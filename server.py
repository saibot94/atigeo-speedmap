from flask import Flask, abort, jsonify

app = Flask(__name__, static_url_path="", static_folder="ui")


@app.route('/')
def root():
    return app.send_static_file('index.html')

if __name__ == '__main__':
    print 'App is running at localhost:5000'
    app.run(debug=False)
