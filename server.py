from flask import Flask, abort, jsonify

app = Flask(__name__, static_url_path="", static_folder="ui")

if __name__ == '__main__':
    print 'App is running at localhost:5000'
    app.run(debug=False)
