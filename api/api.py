import ConfigParser

from flask import Flask
from flask import jsonify
from flask import make_response
from flask import request

from domain.mongo import get_points_with_weight

app = Flask(__name__)


app_conf = ConfigParser.ConfigParser()
app_conf.read("atism.ini")


LEGAL_SPEED_LIMIT = app_conf.get("Legal", "speed")


@app.after_request
def after_request(response):
  return response


@app.route('/points', methods=["GET"])
def get_drive_points():
    start_ts = request.args.get('start_ts')
    end_ts = request.args.get('end_ts')

    points = get_points_with_weight(count=500)

    response = make_response(jsonify({"points": points}))
    response.headers.add('Access-Control-Allow-Origin', '*')
    response.headers.add('Access-Control-Allow-Headers', 'Content-Type, Authorization')
    response.headers.add('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE')

    return response

if __name__ == "__main__":
    app.run(debug=True, port=8080)
