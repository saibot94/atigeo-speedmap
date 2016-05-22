import numpy as np
from pymongo import MongoClient
from geopy.geocoders import Nominatim

MONGO_HOST = "52.53.195.124"
DB = "hacktm"
client = MongoClient(host=MONGO_HOST)
db = client.get_database(DB)
geolocator = Nominatim()

FIELDS = {
    'latitude': 1,
    'longitude': 1,
    'unixtime': 1,
    'speedkmh': 1,
    'ingestiontime': 1,
    '_id': 0
}


def get_points(collection, count=None, from_speed=None, start_ts=None, end_ts=None, box=None, realtime=False):
    query_conditions = [{"speed": {"$gte": from_speed}}]
    if box:
        nlat = box['northeastern']['lat']
        elong = box['northeastern']['long']
        slat = box['southwestern']['lat']
        wlong = box['southwestern']['lang']
        query_conditions.append({"and": [{"latitude":  {"$lte": nlat}},
                                         {"latitude":  {"$gte": slat}},
                                         {"longitude": {"$gte": wlong}},
                                         {"longitude": {"$lte": elong}}]})

    if realtime:
        query_conditions.append({"ingestiontime": {"$gte": int(start_ts)}})

    if start_ts and not realtime:
        query_conditions.append({"unixtime": {"$gte": start_ts}})

    if end_ts:
        query_conditions.append({"unixtime": {"$lte": end_ts}})

    if len(query_conditions) == 1:
        query = query_conditions[0]
    else:
        query = {"$and": query_conditions}

    collection = db.get_collection(collection)
    points_cursor = collection.find(query, FIELDS)

    return points_cursor if not count else points_cursor.limit(count)


def new_point(point):
    speed = point['speedkmh']
    if 40 < speed < 50:
        display = speed / 1.2456
    elif 50 < speed < 60:
        display = speed 
    else: 
       display = speed * 1.22

    new_point = {}
    for k, v in point.iteritems():
        if k == 'speed': 
            new_point['weight'] = display
        else:
            new_point[k] = v

    return new_point


def get_points_with_weight(collection, count=None, from_speed=None, start_ts=None, end_ts=None, box=None, realtime=False):
    points = get_points(collection, count=count, from_speed=from_speed, start_ts=start_ts, end_ts=end_ts, box=box, realtime=realtime)
    points_with_weight = [new_point(point) for point in points]
    return points_with_weight


def get_speed_stats(collection):
    collection = db.get_collection(collection)
    data = collection.find({}, {"speedkmh": 1, "_id": 0})

    total_speed = 0.0
    total_legal_speed = 0.0
    legal_cnt = 0
    total_illegal_speed = 0.0
    illegal_cnt = 0
    for point in data:
        speed = float(point['speedkmh'])
        total_speed += speed
        if speed > 50.0:
            total_illegal_speed += speed
            illegal_cnt += 1
        else:
            total_legal_speed += speed
            legal_cnt += 1


    points_cnt = data.count()
    main_avg = total_speed / points_cnt
    legal_avg = total_legal_speed / legal_cnt
    illegal_avg = total_illegal_speed / illegal_cnt

    return {'main_avg': main_avg, 'legal_avg': legal_avg, 'illegal_avg': illegal_avg}


def get_dangerous_streets(collection):
    # collection = db.get_collection(collection)
    # fields = {"latitude": 1, "longitude": 1, "_id": 0}
    # dangerous = list(collection.find({"speedkmh": {"$gte": 65.0}}, fields).limit(120))
    # unique_points = list(np.unique(np.array(dangerous)))
    # addresses = []
    # for point in unique_points:
    #     location = geolocator.reverse(str(point['latitude']) + ", " + str(point['longitude']))
    #     addresses.append(location.address)

    # TODO: optimize computation. Don't use the "cache" below
    return [
        "Bulevardul 16 Decembrie 1989, Elisabetin",
        "C. Brancoveanu, Bulevardul 16 Decembrie 1989, Elisabetin",
        "Statie Taxi, Piata Alexandru Mocioni, Elisabetin",
        "Bulevardul 16 Decembrie 1989, Elisabetin",
        "Bulevardul 16 Decembrie 1989, Elisabetin",
        "Bulevardul Doctor Victor Babes, Elisabetin",
        "Piata Mocioni, Bulevardul 16 Decembrie 1989",
        "Ciprian Porumbescu, Strada Ciprian Porumbescu, Elisabetin",
        "Strada Ciprian Porumbescu, Elisabetin, Timisoara",
        "Strada Putna, Complexul Studentesc"
    ]


def get_illegalities_count(collection):
    collection = db.get_collection(collection)
    return collection.find({"speedkmh": {"$gte": 50.0}}).count()

