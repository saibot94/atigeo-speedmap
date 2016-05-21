from pymongo import MongoClient

MONGO_HOST = "52.53.195.124"
DB = "hacktm"

client = MongoClient(host=MONGO_HOST)
db = client.get_database(DB)

DISPLAY_SPEED = 10  # TODO: get from config


def get_points(count=None):
    points_cursor = db.drives.find({"speed": {"$gte": DISPLAY_SPEED}},
                                   {'latitude': 1, 'longitude': 1, 'speedkmh': 1, '_id': 0})
    return points_cursor if not count else points_cursor.limit(count)
