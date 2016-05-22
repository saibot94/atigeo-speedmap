import ConfigParser

from flask import Flask
from flask import jsonify
from flask import make_response
from flask import request
from flask.ext.cors import CORS


from domain.mongo import get_points_with_weight

app = Flask(__name__)
CORS(app)


app_conf = ConfigParser.ConfigParser()
app_conf.read("atism.ini")


LEGAL_SPEED_LIMIT = app_conf.get("Legal", "speed")


@app.route('/points', methods=["GET"])
def get_drive_points():
    start_ts = request.args.get('start_ts')
    end_ts = request.args.get('end_ts')

    points = get_points_with_weight(count=10000)

    response = make_response(jsonify({"points": points}))

    return response

if __name__ == "__main__":
    app.run(debug=True, host="0.0.0.0", port=8080)
