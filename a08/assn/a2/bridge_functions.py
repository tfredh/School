"""Assignment 2: Bridges

The data used for this assignment is a subset of the data found in:
https://data.ontario.ca/dataset/bridge-conditions

This code is provided solely for the personal and private use of
students taking the CSCA08 course at the University of Toronto
Scarborough. Copying for purposes other than this use is expressly
prohibited. All forms of distribution of this code, whether as given
or with any changes, are expressly prohibited.

All of the files in this directory and all subdirectories are:
Copyright (c) 2023 Anya Tafliovich, Mario Badr, Tom Fairgrieve, Sadia
Sharmin, and Jacqueline Smith

"""

import csv
from copy import deepcopy
from math import sin, cos, asin, radians, sqrt, inf
from typing import TextIO

from constants import (
    ID_INDEX, NAME_INDEX, HIGHWAY_INDEX, LAT_INDEX,
    LON_INDEX, YEAR_INDEX, LAST_MAJOR_INDEX,
    LAST_MINOR_INDEX, NUM_SPANS_INDEX,
    SPAN_DETAILS_INDEX, LENGTH_INDEX,
    LAST_INSPECTED_INDEX, BCIS_INDEX, FROM_SEP, TO_SEP,
    HIGH_PRIORITY_BCI, MEDIUM_PRIORITY_BCI,
    LOW_PRIORITY_BCI, HIGH_PRIORITY_RADIUS,
    MEDIUM_PRIORITY_RADIUS, LOW_PRIORITY_RADIUS,
    EARTH_RADIUS)
EPSILON = 0.01


# We provide this function for you to use as a helper.
def read_data(csv_file: TextIO) -> list[list[str]]:
    """Read and return the contents of the open CSV file csv_file as a
    list of lists, where each inner list contains the values from one
    line of csv_file.

    Docstring examples not given since the function reads from a file.

    """

    lines = csv.reader(csv_file)
    return list(lines)[2:]


def calculate_distance(lat1: float, lon1: float,
                       lat2: float, lon2: float) -> float:
    """Return the distance in kilometers between the two locations defined by
    (lat1, lon1) and (lat2, lon2), rounded to the nearest meter.

    >>> abs(calculate_distance(43.659777, -79.397383, 43.657129, -79.399439)
    ...     - 0.338) < EPSILON
    True
    >>> abs(calculate_distance(43.42, -79.24, 53.32, -113.30)
    ...     - 2713.226) < EPSILON
    True
    """

    lat1, lon1, lat2, lon2 = (radians(lat1), radians(lon1),
                              radians(lat2), radians(lon2))

    haversine = (sin((lat2 - lat1) / 2) ** 2
                 + cos(lat1) * cos(lat2) * sin((lon2 - lon1) / 2) ** 2)

    return round(2 * EARTH_RADIUS * asin(sqrt(haversine)), 3)


# We provide this sample data to help you set up example calls.
THREE_BRIDGES_UNCLEANED = [
    ['1 -  32/', 'Highway 24 Underpass at Highway 403', '403', '43.167233',
     '-80.275567', '1965', '2014', '2009', '4',
     'Total=64  (1)=12;(2)=19;(3)=21;(4)=12;', '65', '04/13/2012', '72.3', '',
     '72.3', '', '69.5', '', '70', '', '70.3', '', '70.5', '', '70.7', '72.9',
     ''],
    ['1 -  43/', 'WEST STREET UNDERPASS', '403', '43.164531', '-80.251582',
     '1963', '2014', '2007', '4',
     'Total=60.4  (1)=12.2;(2)=18;(3)=18;(4)=12.2;', '61', '04/13/2012',
     '71.5', '', '71.5', '', '68.1', '', '69', '', '69.4', '', '69.4', '',
     '70.3', '73.3', ''],
    ['2 -   4/', 'STOKES RIVER BRIDGE', '6', '45.036739', '-81.33579', '1958',
     '2013', '', '1', 'Total=16  (1)=16;', '18.4', '08/28/2013', '85.1',
     '85.1', '', '67.8', '', '67.4', '', '69.2', '70', '70.5', '', '75.1', '',
     '90.1', '']
]

THREE_BRIDGES = [
    [1, 'Highway 24 Underpass at Highway 403', '403', 43.167233, -80.275567,
     '1965', '2014', '2009', 4, [12.0, 19.0, 21.0, 12.0], 65.0, '04/13/2012',
     [72.3, 69.5, 70.0, 70.3, 70.5, 70.7, 72.9]],
    [2, 'WEST STREET UNDERPASS', '403', 43.164531, -80.251582,
     '1963', '2014', '2007', 4, [12.2, 18.0, 18.0, 12.2], 61.0, '04/13/2012',
     [71.5, 68.1, 69.0, 69.4, 69.4, 70.3, 73.3]],
    [3, 'STOKES RIVER BRIDGE', '6', 45.036739, -81.33579,
     '1958', '2013', '', 1, [16.0], 18.4, '08/28/2013',
     [85.1, 67.8, 67.4, 69.2, 70.0, 70.5, 75.1, 90.1]]
]


# We provide the header and doctring for this function to help get you
# started.
def get_bridge(bridge_data: list[list], bridge_id: int) -> list:
    """Return the data for the bridge with id bridge_id from bridge data
    bridge_data. If there is no bridge with id bridge_id, return [].

    >>> result = get_bridge(THREE_BRIDGES, 1)
    >>> result == [
    ...    1, 'Highway 24 Underpass at Highway 403', '403', 43.167233,
    ...    -80.275567, '1965', '2014', '2009', 4,
    ...    [12.0, 19.0, 21.0, 12.0], 65.0, '04/13/2012',
    ...    [72.3, 69.5, 70.0, 70.3, 70.5, 70.7, 72.9]]
    True
    >>> get_bridge(THREE_BRIDGES, 42)
    []
    """

    for bridge in bridge_data:
        if bridge[ID_INDEX] == bridge_id:
            return bridge

    return []


def get_average_bci(bridge_data: list[list], bridge_id: int) -> float:
    """
    Return the average BCI of the bridge in bridges, `bridge_data` with 
    the given id, `bridge_id`, rounded to 4 decimal places. If there is 
    no bridge with the given id, 
    the function should return zero. If there are no BCIs for the bridge 
    with the given id, the function should return zero.

    >>> get_average_bci(THREE_BRIDGES, 1)
    70.8857
    >>> get_average_bci(THREE_BRIDGES, 999999) # no bridge with id
    0
    >>> get_average_bci([ # no bcis
    ...        [3, 'STOKES RIVER BRIDGE', '6', 45.036739, -81.33579,
    ...        '1958', '2013', '', 1, [16.0], 18.4, '08/28/2013',
    ...        []]
    ...    ],
    ...    3)
    0
    >>> get_average_bci([ # only one bci
    ...        [3, 'STOKES RIVER BRIDGE', '6', 45.036739, -81.33579,
    ...        '1958', '2013', '', 1, [16.0], 18.4, '08/28/2013',
    ...        [2.33]]
    ...    ],
    ...    3)
    2.33
    """
    bridge = get_bridge(bridge_data, bridge_id)
    if not bridge:
        return 0

    bridge_bcis = bridge[BCIS_INDEX]
    avg_bci = sum(bridge_bcis)
    return round(avg_bci / len(bridge_bcis), 4) if avg_bci > 0 else avg_bci


def get_total_length_on_hwy(bridge_data: list[list], highway: str) -> float:
    """
    Return the total length of bridges in `bridge_data` on highway, `highway`. 
    If there are no bridges on the highway, the function should return zero.

    >>> get_total_length_on_hwy(THREE_BRIDGES, '403')
    126.0
    >>> get_total_length_on_hwy(THREE_BRIDGES, 'non-existent-highway')
    0
    """

    highway_len = 0

    for bridge in bridge_data:
        if bridge[HIGHWAY_INDEX] == highway:
            highway_len += bridge[LENGTH_INDEX]

    return highway_len


def get_distance_between(bridge1: list, bridge2: list) -> float:
    """
    Returns the distance in kilometres, rounded to the nearest metre 
    (i.e., 3 decimal places), between two bridges, `bridge` and `bridge2`.


    >>> get_distance_between(
    ...    [1, 'Highway 24 Underpass at Highway 403', '403', 43.167233, 
    ...     -80.275567, '1965', '2014', '2009', 4, [12.0, 19.0, 21.0, 12.0], 
    ...     65.0, '04/13/2012', [72.3, 69.5, 70.0, 70.3, 70.5, 70.7, 72.9]],
    ...    [2, 'WEST STREET UNDERPASS', '403', 43.164531, -80.251582, '1963', 
    ...     '2014', '2007', 4, [12.2, 18.0, 18.0, 12.2], 61.0, '04/13/2012', 
    ...     [71.5, 68.1, 69.0, 69.4, 69.4, 70.3, 73.3]]
    ... )
    1.968
    >>> get_distance_between( # same location
    ...    [1, 'Highway 24 Underpass at Highway 403', '403', 43.167233, 
    ...     -80.275567, '1965', '2014', '2009', 4, [12.0, 19.0, 21.0, 12.0],
    ...     65.0, '04/13/2012', [72.3, 69.5, 70.0, 70.3, 70.5, 70.7, 72.9]],
    ...    [2, 'WEST STREET UNDERPASS', '403', 43.167233, -80.275567, '1963',
    ...     '2014', '2007', 4, [12.2, 18.0, 18.0, 12.2], 61.0, '04/13/2012',
    ...     [71.5, 68.1, 69.0, 69.4, 69.4, 70.3, 73.3]]
    ... )
    0.0
    """

    return calculate_distance(
        bridge1[LAT_INDEX],
        bridge1[LON_INDEX],
        bridge2[LAT_INDEX],
        bridge2[LON_INDEX]
    )


def get_closest_bridge(bridge_data: list[list], bridge_id: int) -> int:
    """
    Returns the id of a bridge in `bridge_data` that has the shortest distance 
    to the bridge with the given id. (The function should not return the bridge 
    with the given id itself. If there is a tie, the function should return
    the id of the bridge that appears first in `bridge_data`.

    Precondition:
    - the bridge with the given id is present in the `bridge_data`
    - there are at least two bridge in the `bridge_data`

    >>> get_closest_bridge(THREE_BRIDGES, 2)
    1
    """

    origin_bridge = get_bridge(bridge_data, bridge_id)

    closest = None
    closest_dist = float('inf')

    for bridge in bridge_data:
        if bridge[ID_INDEX] == bridge_id:
            continue

        dist = get_distance_between(bridge, origin_bridge)
        if dist < closest_dist:
            closest = bridge
            closest_dist = dist

    return closest[ID_INDEX]


def get_bridges_in_radius(
    bridge_data: list[list],
    lat: float,
    lon: float,
    radius: float
) -> list[int]:
    """
    Returns a list of ids of all bridges in `bridges_data` that are within the
    distance, `radius` of the given location, (`lat`, `lon`).

    >>> get_bridges_in_radius(THREE_BRIDGES, 43.10, -80.15, 50)
    [1, 2]
    >>> get_bridges_in_radius(THREE_BRIDGES[:2], 43.10, -80.15, 50)
    [1, 2]
    >>> get_bridges_in_radius(THREE_BRIDGES[:1], 43.10, -80.15, 50)
    [1]
    >>> get_bridges_in_radius(THREE_BRIDGES[2:], 43.10, -80.15, 50)
    []
    >>> get_bridges_in_radius([], 43.10, -80.15, 50)
    []
    """

    bridges_in_radius = []
    for bridge in bridge_data:
        if calculate_distance(
            bridge[LAT_INDEX],
            bridge[LON_INDEX],
            lat,
            lon
        ) < radius:
            bridges_in_radius.append(bridge[ID_INDEX])

    return bridges_in_radius


def get_bridges_with_bci_below(
    bridge_data: list[list],
    bridge_ids: list[int],
    ref_bci: float
) -> list[int]:
    """
    Returns a list of ids of all bridges in `bridge_data` whose ids are in the
    list of ids, `bridge_ids` and whose BCI is less than or equal to the 
    reference BCI, ref_bci.

    >>> get_bridges_with_bci_below(THREE_BRIDGES, [1, 2], 72)
    [2]
    >>> get_bridges_with_bci_below(THREE_BRIDGES, [1], 72)
    []
    >>> get_bridges_with_bci_below(THREE_BRIDGES, [1, 2, 3], 72)
    [2]

    >>> test_bridge = deepcopy(THREE_BRIDGES)
    >>> test_bridge[2][BCIS_INDEX][0] = 1.0
    >>> get_bridges_with_bci_below(test_bridge, [1, 2, 3], 72)
    [2, 3]
    """

    bridge_ids_set = set(bridge_ids)
    bridges_bci_below = []

    for bridge in bridge_data:
        if bridge[ID_INDEX] not in bridge_ids_set:
            continue

        if bridge[BCIS_INDEX][0] <= ref_bci:
            bridges_bci_below.append(bridge[ID_INDEX])

    return bridges_bci_below


def get_bridges_containing(bridge_data: list[list], search: str) -> list[int]:
    """
    Returns a list of ids of all bridges in `bridge_data` whose names 
    contain the search string, `search`. The search should be case-insensitive.

    When called with the example THREE_BRIDGES and the search string 'underpass', 
    the function should return the list [1, 2]. Note that when called with the 
    example THREE_BRIDGES and the search string 'pass', the function should also 
    return the list [1, 2], i.e. the function looks for part of the name, not 
    necessarily the entire name.

    >>> get_bridges_containing(THREE_BRIDGES, 'underpass')
    [1, 2]
    >>> get_bridges_containing(THREE_BRIDGES, 'pass')
    [1, 2]
    >>> get_bridges_containing(THREE_BRIDGES, 'asd')
    []
    >>> get_bridges_containing(THREE_BRIDGES, 'brid')
    [3]
    """

    containing_search = []

    for bridge in bridge_data:
        if search.lower() in bridge[NAME_INDEX].lower():
            containing_search.append(bridge[ID_INDEX])

    return containing_search


# We provide the header and doctring for this function to help get you
# started. Note the use of the built-in function deepcopy (see
# help(deepcopy)!): since this function modifies its input, we do not
# want to call it with THREE_BRIDGES, which would interfere with the
# use of THREE_BRIDGES in examples for other functions.
def inspect_bridges(bridge_data: list[list], bridge_ids: list[int], date: str,
                    bci: float) -> None:
    """Update the bridges in bridge_data with id in bridge_ids with the new
    date and BCI score for a new inspection.

    >>> bridges = deepcopy(THREE_BRIDGES)
    >>> inspect_bridges(bridges, [1], '09/15/2018', 71.9)
    >>> bridges[1:] == THREE_BRIDGES[1:]
    True
    >>> bridges[0] == THREE_BRIDGES[0]
    False
    >>> bridges[0][LAST_INSPECTED_INDEX] == THREE_BRIDGES[0][LAST_INSPECTED_INDEX]
    False
    >>> bridges[0][BCIS_INDEX] == THREE_BRIDGES[0][BCIS_INDEX]
    False
    >>> bridges == [
    ...   [1, 'Highway 24 Underpass at Highway 403', '403',
    ...    43.167233, -80.275567, '1965', '2014', '2009', 4,
    ...    [12.0, 19.0, 21.0, 12.0], 65, '09/15/2018',
    ...    [71.9, 72.3, 69.5, 70.0, 70.3, 70.5, 70.7, 72.9]],
    ...   [2, 'WEST STREET UNDERPASS', '403', 43.164531, -80.251582,
    ...    '1963', '2014', '2007', 4, [12.2, 18.0, 18.0, 12.2],
    ...    61, '04/13/2012', [71.5, 68.1, 69.0, 69.4, 69.4, 70.3, 73.3]],
    ...   [3, 'STOKES RIVER BRIDGE', '6', 45.036739, -81.33579,
    ...    '1958', '2013', '', 1, [16.0], 18.4, '08/28/2013',
    ...    [85.1, 67.8, 67.4, 69.2, 70.0, 70.5, 75.1, 90.1]]]
    True

    >>> inspect_bridges(bridges, [2, 3], '09/15/2030', 55.0)
    >>> bridges == [
    ...   [1, 'Highway 24 Underpass at Highway 403', '403',
    ...    43.167233, -80.275567, '1965', '2014', '2009', 4,
    ...    [12.0, 19.0, 21.0, 12.0], 65, '09/15/2018',
    ...    [71.9, 72.3, 69.5, 70.0, 70.3, 70.5, 70.7, 72.9]],
    ...   [2, 'WEST STREET UNDERPASS', '403', 43.164531, -80.251582,
    ...    '1963', '2014', '2007', 4, [12.2, 18.0, 18.0, 12.2],
    ...    61, '09/15/2030', [55.0, 71.5, 68.1, 69.0, 69.4, 69.4, 70.3, 73.3]],
    ...   [3, 'STOKES RIVER BRIDGE', '6', 45.036739, -81.33579,
    ...    '1958', '2013', '', 1, [16.0], 18.4, '09/15/2030',
    ...    [55.0, 85.1, 67.8, 67.4, 69.2, 70.0, 70.5, 75.1, 90.1]]]
    True

    >>> inspect_bridges(bridges, [], '01/01/2050', 100.0)
    >>> bridges == [
    ...   [1, 'Highway 24 Underpass at Highway 403', '403',
    ...    43.167233, -80.275567, '1965', '2014', '2009', 4,
    ...    [12.0, 19.0, 21.0, 12.0], 65, '09/15/2018',
    ...    [71.9, 72.3, 69.5, 70.0, 70.3, 70.5, 70.7, 72.9]],
    ...   [2, 'WEST STREET UNDERPASS', '403', 43.164531, -80.251582,
    ...    '1963', '2014', '2007', 4, [12.2, 18.0, 18.0, 12.2],
    ...    61, '09/15/2030', [55.0, 71.5, 68.1, 69.0, 69.4, 69.4, 70.3, 73.3]],
    ...   [3, 'STOKES RIVER BRIDGE', '6', 45.036739, -81.33579,
    ...    '1958', '2013', '', 1, [16.0], 18.4, '09/15/2030',
    ...    [55.0, 85.1, 67.8, 67.4, 69.2, 70.0, 70.5, 75.1, 90.1]]]
    True
    """

    bridge_ids_set = set(bridge_ids)

    for bridge in bridge_data:
        if bridge[ID_INDEX] not in bridge_ids_set:
            continue

        bridge[LAST_INSPECTED_INDEX] = date
        bridge[BCIS_INDEX].insert(0, bci)


def add_rehab(bridge_data: list[list], bridge_id: int, date: str,
              major_rehab: bool) -> None:
    """
    Updates the bridges in `bridge_data` with the given ID, `bridge_id` with 
    the new rehab year record: year of major rehab, if the last argument is 
    True, and year or minor rehab if the last argument is False. If there is 
    no bridge with the given id in the given bridge data, the function has no 
    effect.

    >>> bridges = deepcopy(THREE_BRIDGES)
    >>> add_rehab(bridges, 1, '09/15/2023', False)
    >>> bridges == [
    ...    [1, 'Highway 24 Underpass at Highway 403', '403', 43.167233, -80.275567,
    ...    '1965', '2014', '2023', 4, [12.0, 19.0, 21.0, 12.0], 65, '04/13/2012',
    ...    [72.3, 69.5, 70.0, 70.3, 70.5, 70.7, 72.9]],
    ...    [2, 'WEST STREET UNDERPASS', '403', 43.164531, -80.251582,
    ...    '1963', '2014', '2007', 4, [12.2, 18.0, 18.0, 12.2], 61.0, '04/13/2012',
    ...    [71.5, 68.1, 69.0, 69.4, 69.4, 70.3, 73.3]],
    ...    [3, 'STOKES RIVER BRIDGE', '6', 45.036739, -81.33579,
    ...    '1958', '2013', '', 1, [16.0], 18.4, '08/28/2013',
    ...    [85.1, 67.8, 67.4, 69.2, 70.0, 70.5, 75.1, 90.1]]
    ... ]
    True
    """

    for bridge in bridge_data:
        if not bridge[ID_INDEX] == bridge_id:
            continue

        bridge[
            LAST_MAJOR_INDEX
            if major_rehab
            else LAST_MINOR_INDEX
        ] = date[-4:]


# # We provide the header and doctring for this function to help get you started.
# def assign_inspectors(bridge_data: list[list], inspectors: list[list[float]],
#                       max_bridges: int) -> list[list[int]]:
#     """Return a list of bridge IDs from bridge data bridge_data, to be
#     assigned to each inspector in inspectors. inspectors is a list
#     containing (latitude, longitude) pairs representing each
#     inspector's location. At most max_bridges are assigned to each
#     inspector, and each bridge is assigned once (to the first
#     inspector that can inspect that bridge).

#     See the "Assigning Inspectors" section of the handout for more details.

#     >>> assign_inspectors(THREE_BRIDGES, [[43.10, -80.15], [42.10, -81.15]], 0)
#     [[], []]
#     >>> assign_inspectors(THREE_BRIDGES, [[43.10, -80.15]], 1)
#     [[1]]
#     >>> assign_inspectors(THREE_BRIDGES, [[43.10, -80.15]], 2)
#     [[1, 2]]
#     >>> assign_inspectors(THREE_BRIDGES, [[43.10, -80.15]], 3)
#     [[1, 2]]
#     >>> assign_inspectors(THREE_BRIDGES, [[43.20, -80.35], [43.10, -80.15]], 1)
#     [[1], [2]]
#     >>> assign_inspectors(THREE_BRIDGES, [[43.20, -80.35], [43.10, -80.15]], 2)
#     [[1, 2], []]
#     >>> assign_inspectors(THREE_BRIDGES, [[43.20, -80.35], [45.0368, -81.34]],
#     ...                   2)
#     [[1, 2], [3]]
#     >>> assign_inspectors(THREE_BRIDGES, [[38.691, -80.85], [43.20, -80.35]],
#     ...                   2)
#     [[], [1, 2]]

#     """

#     pass


# We provide the header and doctring for this function to help get you started.
THREE_BRIDGES = [
    [1, 'Highway 24 Underpass at Highway 403', '403', 43.167233, -80.275567,
     '1965', '2014', '2009', 4, [12.0, 19.0, 21.0, 12.0], 65.0, '04/13/2012',
     [72.3, 69.5, 70.0, 70.3, 70.5, 70.7, 72.9]],
    [2, 'WEST STREET UNDERPASS', '403', 43.164531, -80.251582,
     '1963', '2014', '2007', 4, [12.2, 18.0, 18.0, 12.2], 61.0, '04/13/2012',
     [71.5, 68.1, 69.0, 69.4, 69.4, 70.3, 73.3]],
    [3, 'STOKES RIVER BRIDGE', '6', 45.036739, -81.33579,
     '1958', '2013', '', 1, [16.0], 18.4, '08/28/2013',
     [85.1, 67.8, 67.4, 69.2, 70.0, 70.5, 75.1, 90.1]]
]
THREE_BRIDGES_UNCLEANED = [
    ['1 -  32/', 'Highway 24 Underpass at Highway 403', '403', '43.167233',
     '-80.275567', '1965', '2014', '2009', '4',
     'Total=64  (1)=12;(2)=19;(3)=21;(4)=12;', '65', '04/13/2012', '72.3', '',
     '72.3', '', '69.5', '', '70', '', '70.3', '', '70.5', '', '70.7', '72.9',
     ''],
    ['1 -  43/', 'WEST STREET UNDERPASS', '403', '43.164531', '-80.251582',
     '1963', '2014', '2007', '4',
     'Total=60.4  (1)=12.2;(2)=18;(3)=18;(4)=12.2;', '61', '04/13/2012',
     '71.5', '', '71.5', '', '68.1', '', '69', '', '69.4', '', '69.4', '',
     '70.3', '73.3', ''],
    ['2 -   4/', 'STOKES RIVER BRIDGE', '6', '45.036739', '-81.33579', '1958',
     '2013', '', '1', 'Total=16  (1)=16;', '18.4', '08/28/2013', '85.1',
     '85.1', '', '67.8', '', '67.4', '', '69.2', '70', '70.5', '', '75.1', '',
     '90.1', '']
]


def format_data(data: list[list[str]]) -> None:
    """Modify the uncleaned bridge data data, so that it contains proper
    bridge data, i.e., follows the format outlined in the 'Data
    formatting' section of the assignment handout.

    >>> d = THREE_BRIDGES_UNCLEANED
    >>> format_data(d)
    >>> d == THREE_BRIDGES
    True
    """

    for i in range(len(data)):
        unformatted_bridge = data[i]

        # bridge ID
        unformatted_bridge[ID_INDEX] = i + 1

        # bridge Name
        unformatted_bridge[NAME_INDEX] = unformatted_bridge[NAME_INDEX]

        # bridge Highway
        unformatted_bridge[HIGHWAY_INDEX] = unformatted_bridge[HIGHWAY_INDEX]

        # bridge Latitude
        # bridge Longitude
        format_location(unformatted_bridge)

        # bridge Year Built
        unformatted_bridge[YEAR_INDEX] = unformatted_bridge[YEAR_INDEX]

        # bridge Last Major Rehab
        unformatted_bridge[LAST_MAJOR_INDEX] = unformatted_bridge[LAST_MAJOR_INDEX]

        # bridge Last Minor Rehab
        unformatted_bridge[LAST_MINOR_INDEX] = unformatted_bridge[LAST_MINOR_INDEX]

        # bridge Number of Spans
        # bridge Span Details
        format_spans(unformatted_bridge)

        # bridge Bridge Length
        format_length(unformatted_bridge)

        # bridge Last Inspected Date -- already in proper date format

        # bridge BCIs
        format_bcis(unformatted_bridge)


# This is a suggested helper function for format_data. We provide the
# header and doctring for this function to help you structure your
# solution.
def format_spans(bridge_record: list) -> None:
    """Format the bridge spans data in the bridge record bridge_record.

    >>> record = ['1 -  32/', 'Highway 24 Underpass at Highway 403', '403',
    ...           '43.167233', '-80.275567', '1965', '2014', '2009', '4',
    ...           'Total=64  (1)=12;(2)=19;(3)=21;(4)=12;', '65', '04/13/2012',
    ...           '72.3', '', '72.3', '', '69.5', '', '70', '', '70.3', '',
    ...           '70.5', '', '70.7', '72.9', '']
    >>> format_spans(record)
    >>> record == ['1 -  32/', 'Highway 24 Underpass at Highway 403', '403',
    ...           '43.167233', '-80.275567', '1965', '2014', '2009', 4,
    ...           [12.0, 19.0, 21.0, 12.0], '65', '04/13/2012',
    ...           '72.3', '', '72.3', '', '69.5', '', '70', '', '70.3', '',
    ...           '70.5', '', '70.7', '72.9', '']
    True
    """

    # bridge Number of Spans
    bridge_record[NUM_SPANS_INDEX] = int(bridge_record[NUM_SPANS_INDEX])

    # bridge Span Details
    span_details: str = bridge_record[SPAN_DETAILS_INDEX]
    span_froms = span_details.split(FROM_SEP)[2:]

    formatted_spans = [
        float(span[: span.index(TO_SEP)])
        for span
        in span_froms
    ]

    bridge_record[SPAN_DETAILS_INDEX] = formatted_spans


# This is a suggested helper function for format_data. We provide the
# header and doctring for this function to help you structure your
# solution.
def format_location(bridge_record: list) -> None:
    """Format latitude and longitude data in the bridge record bridge_record.

    >>> record = ['1 -  32/', 'Highway 24 Underpass at Highway 403', '403',
    ...           '43.167233', '-80.275567', '1965', '2014', '2009', '4',
    ...           'Total=64  (1)=12;(2)=19;(3)=21;(4)=12;', '65', '04/13/2012',
    ...           '72.3', '', '72.3', '', '69.5', '', '70', '', '70.3', '',
    ...           '70.5', '', '70.7', '72.9', '']
    >>> format_location(record)
    >>> record == ['1 -  32/', 'Highway 24 Underpass at Highway 403', '403',
    ...           43.167233, -80.275567, '1965', '2014', '2009', '4',
    ...           'Total=64  (1)=12;(2)=19;(3)=21;(4)=12;', '65', '04/13/2012',
    ...           '72.3', '', '72.3', '', '69.5', '', '70', '', '70.3', '',
    ...           '70.5', '', '70.7', '72.9', '']
    True
    """

    bridge_record[LAT_INDEX] = float(bridge_record[LAT_INDEX])
    bridge_record[LON_INDEX] = float(bridge_record[LON_INDEX])


# This is a suggested helper function for format_data. We provide the
# header and doctring for this function to help you structure your
# solution.
def format_length(bridge_record: list) -> None:
    """Format the bridge length data in the bridge record bridge_record.

    >>> record = ['1 -  32/', 'Highway 24 Underpass at Highway 403', '403',
    ...           '43.167233', '-80.275567', '1965', '2014', '2009', '4',
    ...           'Total=64  (1)=12;(2)=19;(3)=21;(4)=12;', '65', '04/13/2012',
    ...           '72.3', '', '72.3', '', '69.5', '', '70', '', '70.3', '',
    ...           '70.5', '', '70.7', '72.9', '']
    >>> format_length(record)
    >>> record == ['1 -  32/', 'Highway 24 Underpass at Highway 403', '403',
    ...            '43.167233', '-80.275567', '1965', '2014', '2009', '4',
    ...            'Total=64  (1)=12;(2)=19;(3)=21;(4)=12;', 65, '04/13/2012',
    ...            '72.3', '', '72.3', '', '69.5', '', '70', '', '70.3', '',
    ...            '70.5', '', '70.7', '72.9', '']
    True
    """

    bridge_record[LENGTH_INDEX] = (
        float(bridge_record[LENGTH_INDEX])
        if len(bridge_record[LENGTH_INDEX])
        else 0.0
    )


# This is a suggested helper function for format_data. We provide the
# header and doctring for this function to help you structure your
# solution.
def format_bcis(bridge_record: list) -> None:
    """Format the bridge BCI data in the bridge record bridge_record.
    >>> record = ['1 -  32/', 'Highway 24 Underpass at Highway 403', '403',
    ...           '43.167233', '-80.275567', '1965', '2014', '2009', '4',
    ...           'Total=64  (1)=12;(2)=19;(3)=21;(4)=12;', '65', '04/13/2012',
    ...           '72.3', '', '72.3', '', '69.5', '', '70', '', '70.3', '',
    ...           '70.5', '', '70.7', '72.9', '']
    >>> format_bcis(record)

    >>> record[:-1] == ['1 -  32/', 'Highway 24 Underpass at Highway 403', '403',
    ...           '43.167233', '-80.275567', '1965', '2014', '2009', '4',
    ...           'Total=64  (1)=12;(2)=19;(3)=21;(4)=12;', '65', '04/13/2012']
    True
    >>> record[-1] == [72.3, 69.5, 70.0, 70.3, 70.5, 70.7, 72.9]
    True
    >>> record == ['1 -  32/', 'Highway 24 Underpass at Highway 403', '403',
    ...           '43.167233', '-80.275567', '1965', '2014', '2009', '4',
    ...           'Total=64  (1)=12;(2)=19;(3)=21;(4)=12;', '65', '04/13/2012',
    ...           [72.3, 69.5, 70.0, 70.3, 70.5, 70.7, 72.9]]
    True
    """

    formatted_bcis = []

    # skip the first bci since it's repeated
    for i in range(BCIS_INDEX + 1, len(bridge_record)):

        if bridge_record[i] != "":
            formatted_bcis.append(float(bridge_record[i]))

    for i in range(len(bridge_record) - 1, BCIS_INDEX - 1, -1):
        bridge_record.pop()

    bridge_record.append(formatted_bcis)


if __name__ == '__main__':
    import doctest
    doctest.testmod()

    # To test your code with larger lists, you can uncomment the code below to
    # read data from the provided CSV file.
    # with open('bridge_data.csv', encoding='utf-8') as bridge_data_file:
    #     BRIDGES = read_data(bridge_data_file)
    # format_data(BRIDGES)

    # For example:
    # print(get_bridge(BRIDGES, 3))
    # EXPECTED = [3, 'NORTH PARK STEET UNDERPASS', '403', 43.165918, -80.263791,
    #             '1962', '2013', '2009', 4, [12.2, 18.0, 18.0, 12.2], 60.8,
    #             '04/13/2012', [71.4, 69.9, 67.7, 68.9, 69.1, 69.9, 72.8]]
    # print('Testing get_bridge: ', get_bridge(BRIDGES, 3) == EXPECTED)
