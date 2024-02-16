import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    info = db.execute(
        "SELECT symbol, SUM(value) value, SUM(shares) shares FROM purchases WHERE userid = ? GROUP BY symbol", session["user_id"])
    data = dict()
    for i in info:
        data[i['symbol']] = {'shares': i['shares'], 'price': usd(lookup(i['symbol'])['price']), 'total': usd(i['value'])}

    q1 = db.execute("SELECT SUM(cash) cash FROM users WHERE id = ?", session["user_id"])[0]['cash']

    if not q1:
        cash = usd(0)
    else:
        cash = usd(db.execute("SELECT SUM(cash) cash FROM users WHERE id = ?", session["user_id"])[0]['cash'])

    q1 = db.execute("SELECT SUM(value) value FROM purchases WHERE userid = ?", session["user_id"])[0]['value']
    if not q1:
        value = usd(0)
    else:
        value = usd(q1)

    return render_template("index.html", info=data.items(), cash=cash, value=value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:

        # Getting symbol from form
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not shares:
            return apology("must provide a number of shares", 400)

        shares = int(shares)

        # Validating if symbol exists
        if not symbol:
            return apology("must provide a symbol", 400)

        # Getting info from symbol
        info = lookup(symbol)
        price = info["price"]

        # Validating if there are info for symbol
        if not info:
            return apology("must provide a valid symbol", 400)

        # Shares must be higher than 0
        if shares < 1:
            return apology("must provide a valid number of shares", 400)

        value = shares*price

        info = db.execute("SELECT id,cash FROM users WHERE username = ?", session["username"])
        cash_available = info[0]['cash']
        userid = session["user_id"]
        username = session["username"]

        if cash_available < value:
            return apology("You don't have enough money for this operation")

        db.execute("UPDATE users SET cash = cash - ? WHERE username = ?", value, username)

        info = db.execute("SELECT symbol, shares FROM purchases WHERE userid = ? AND symbol = ?", userid, symbol)

        # When there is shares bought for that symbol
        if len(info) > 0:

            # Updating buy table
            shares = shares + info[0]["shares"]
            value = shares*price
            db.execute("UPDATE purchases SET shares = ?, value = ?, symbol = ? WHERE userid = ?", shares, value, symbol, symbol)

            # Inserting into history table
            purchid = db.execute("SELECT id FROM purchases WHERE symbol = ? AND userid = ?", symbol, userid)[0]['id']
            date = datetime.now().strftime("%m/%d/%Y, %H:%M:%S")
            db.execute("INSERT INTO history (type, shares, price, time, purchid) VALUES(?, ?, ?, ?, ?)",
                       'Buy', shares, price, date, purchid)

        # When there is not shares bought for that symbol
        else:

            # Inserting into purchase table
            db.execute("INSERT INTO purchases (shares, value, symbol, userid) VALUES(?, ?, ?, ?)", shares, value, symbol, userid)

            # Inserting into history table
            shares = int(request.form.get("shares"))
            purchid = db.execute("SELECT id FROM purchases WHERE symbol = ? AND userid = ?", symbol, userid)[0]['id']
            date = datetime.now().strftime("%m/%d/%Y, %H:%M:%S")
            db.execute("INSERT INTO history (type, shares, price, time, purchid) VALUES(?, ?, ?, ?, ?)",
                       'Buy', shares, price, date, purchid)

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    userid = session["user_id"]
    data = db.execute("SELECT purchases.symbol, history.type, history.shares, history.price, history.time FROM history, users, purchases WHERE history.purchid = purchases.id AND purchases.userid = users.id AND users.id = ?", userid)
    return render_template("history.html", data=data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["username"] = request.form.get("username")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # Render template by clicking Quote
    if request.method == "GET":
        return render_template("quote.html")
    else:

        # Getting symbol from form
        symbol = request.form.get("symbol")

        # Validating if symbol exists
        if not symbol:
            return apology("must provide a symbol", 400)

        # Getting info from symbol
        info = lookup(symbol)

        # Validating if there are info for symbol
        if not info:
            return apology("must provide a valid symbol", 400)

        # Returning a page with queried data
        return render_template("quoted.html", name=info["name"], price=usd(info["price"]), symbol=symbol)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        hash = generate_password_hash(password)
        confirmation = request.form.get("confirmation")

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # If the user already exists
        elif len(rows) != 0:
            return apology("username already exists", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # Checking password validity
        elif password != confirmation:
            return apology("password and confirmation do not match", 400)

        else:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        # Getting the symbol and shares from form
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        # Getting userid
        userid = session["user_id"]

        # Querying for number of shares by selected company
        q1 = db.execute("SELECT SUM(shares) sum_shares FROM purchases WHERE userid = ? AND symbol = ?", userid, symbol)
        shares_symbol = int(q1[0]['sum_shares'])

        # If user don't select a valid symbol
        if symbol == "Select a Stock symbol":
            # Apology
            return apology("select a stock symbol", 400)
        # If number of shares to sell is invalid
        elif shares < 1:
            # Apology
            return apology("introduce a valid number of shares", 400)
        elif shares_symbol < shares:
            # Apology
            return apology("you don't have enough shares for this operation", 400)
        else:
            # Getting info from symbol
            info = lookup(symbol)

            # Getting actual price
            price = info['price']

            # Getting total value for shares
            v = price*shares
            value = price*shares_symbol-v

            # Subtracting shares by operation
            db.execute("UPDATE purchases SET shares = shares - ?, value = ? WHERE userid = ? AND symbol = ?", shares, value, userid, symbol)

            # Adding value when selling shares
            db.execute("UPDATE users SET cash = cash + ?", v)

            # Delete from purchase a symbol when it's shares is equals to 0
            db.execute("DELETE FROM purchases WHERE userid = ? AND symbol = ? AND shares = ?", userid, symbol, 0)

            # Inserting into history table
            purchid = db.execute("SELECT id FROM purchases WHERE symbol = ? AND userid = ?", symbol, userid)[0]['id']
            date = datetime.now().strftime("%m/%d/%Y, %H:%M:%S")
            db.execute("INSERT INTO history (type, shares, price, time, purchid) VALUES(?, ?, ?, ?, ?)",
                       'Sell', shares, price, date, purchid)

            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        symbols = list()
        info = db.execute("SELECT DISTINCT symbol FROM purchases WHERE userid = ?", session["user_id"])
        for i in info:
            for v in i.values():
                symbols.append(v)
        return render_template("sell.html", symbols=symbols)
