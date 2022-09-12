import sys
import math # for sqrt
import random

class Room:
    def __init__(self, x: int, y: int, name = None):
        self.x = x
        self.y = y
        self.name = name

    def __str__(self):
        return str("{}:({}, {})".format(self.name, self.x, self.y))

def ccw(A: 'Room', B: 'Room', C: 'Room') -> bool:
    return (C.y - A.y) * (B.x - A.x) >= (B.y - A.y) * (C.x - A.x)

def intersect(A: 'Room', B: 'Room', C: 'Room', D: 'Room') -> bool:
    if (A.x == C and A.y == C.y) or (A.x == D.x and A.y == D.y) or (B.x == C.x and B.y == C.y) or (B.x == D.x and B.y == D.y):
        return False
    return ccw(A, C, D) != ccw(B, C, D) and ccw(A, B, C) != ccw(A, B, D)

def getDistanceFromLine(p: 'Room', l1: 'Room', l2: 'Room') -> float:
    return abs((l2.y - l1.y) * p.x - (l2.x - l1.x) * p.y + l2.x * l1.y - l2.y * l1.x) / math.sqrt((l2.y - l1.y) ** 2 + (l2.x - l1.x) ** 2)

def print_usage():
    print("Usage: generator.py room_count ant_count")
    sys.exit(1)

try :
    assert len(sys.argv) == 3, "2 argument is provided: room_count and ant_count"
    assert sys.argv[1].isdigit(), "room_count is not a positive number"
    assert sys.argv[2].isdigit(), "ant_count is not a positive number"
except AssertionError as error:
    print("AssertionError:", error.__str__())
    print_usage()
    exit(0)
room_count = int(sys.argv[1])
ant_count = int(sys.argv[2])

#config
map_size_mult = .3
min_distance_to_link = .5
max_links = room_count * .3

maxx = math.ceil(room_count * map_size_mult * 1.6)
maxy = math.ceil(room_count * map_size_mult * 0.9)

rooms = []
links = []
additionnal_links = []

i = 0
j = 0
g_loops = 0

while (j < max_links):
    # generate rooms
    loops = 0
    while rooms.__len__() < room_count:
        loops += 1
        if loops > room_count ** 2:
            loops = 0
        if loops == 0:
            i = 0
            rooms.clear()
            links.clear()
            continue
        x = random.randint(0, maxx)
        y = random.randint(0, maxy)
        if any(room.x == x and room.y == y for room in rooms):
            continue
        if (rooms.__len__() < 1):
            rooms.append(Room(x, y, "room_{}".format(i)))
            i += 1
            continue
        if any(getDistanceFromLine(Room(x, y), link[0], link[1]) < min_distance_to_link for link in links):
            continue
        min_dist = maxx * maxy
        closest_room = None
        for other_room in rooms:
            if any(intersect(Room(x, y), other_room, link[0], link[1]) for link in links):
                continue
            if (x - other_room.x) ** 2 + (y - other_room.y) ** 2 < min_dist:
                min_dist = (x - other_room.x) ** 2 + (y - other_room.y) ** 2
                closest_room = other_room
        if (closest_room == None):
            continue
        rooms.append(Room(x, y, "room_{}".format(i)))
        links.append((rooms[rooms.__len__() - 1], closest_room))
        i += 1

    # generate additionnal links
    loops_2 = 0
    while (j < max_links):
        loops_2 += 1
        if loops_2 > room_count ** 2:
            loops_2 = 0
        if loops_2 == 0:
            j = 0
            additionnal_links.clear()
            g_loops += 1
            continue
        if g_loops > room_count * .5:
            j = 0
            additionnal_links.clear()
            i = 0
            rooms.clear()
            links.clear()
            g_loops = 0
            break
        room = random.choice(rooms)
        other_room = random.choice(rooms)
        if (room == other_room):
            continue
        if any(link[0] == room and link[1] == other_room or link[0] == other_room and link[1] == room for link in links + additionnal_links):
            continue
        if any(intersect(room, other_room, link[0], link[1]) for link in links + additionnal_links):
            continue
        tmp_rooms = rooms.copy()
        tmp_rooms.remove(room)
        tmp_rooms.remove(other_room)
        if any(getDistanceFromLine(room_test, room, other_room) < min_distance_to_link for room_test in tmp_rooms):
            continue
        additionnal_links.append((room, other_room))
        j += 1

links += additionnal_links

# print map
print(ant_count)
already_printed = []
max_dist = 0
room1 = None
room2 = None
for room in rooms:
    for other_room in rooms:
        if room == other_room:
            continue
        dist = (room.x - other_room.x) ** 2 + (room.y - other_room.y) ** 2
        if dist > max_dist:
            max_dist = dist
            room1 = room
            room2 = other_room
print("##start")
print(room1.name, room1.x, room1.y)
print("##end")
print(room2.name, room2.x, room2.y)
already_printed.append(room1)
already_printed.append(room2)
for room in rooms:
    if room in already_printed:
        continue
    print(room.name, room.x, room.y)
for link in links:
    print("{}-{}".format(link[0].name, link[1].name))
