"""CSCA08 Fall 2023 Assignment 1.

This code is provided solely for the personal and private use of
students taking the CSCA08 course at the University of
Toronto. Copying for purposes other than this use is expressly
prohibited. All forms of distribution of this code, whether as given
or with any changes, are expressly prohibited.

All of the files in this directory and all subdirectories are:
Copyright (c) 2020-2023 Jacqueline Smith and Anya Tafliovich.

"""

from constants import (YR, MON, DAY, DEP, ARR, ROW, SEAT, FFN,
                       WINDOW, AISLE, MIDDLE, SA, SB, SC, SD, SE, SF)

# We provide this function solution as an example of correct function
# documentation, as well as a function that uses other functions as
# helpers.


def get_date(ticket: str) -> str:
    """Return the date of ticket 'ticket' in YYYYMMDD format.

    >>> get_date('20230915YYZYEG12F')
    '20230915'
    >>> get_date('20240915YYZYEG12F1236')
    '20240915'
    >>> get_date('20230926DFGKER19D')
    '20230926'
    """

    return get_year(ticket) + get_month(ticket) + get_day(ticket)


# We provide this function solution as an example of correct function
# documentation, as well as a function that uses constants.
def get_year(ticket: str) -> str:
    """Return the year of ticket 'ticket'.

    >>> get_year('20230915YYZYEG12F')
    '2023'
    >>> get_year('20240915YYZYEG12F1236')
    '2024'
    >>> get_year('20230926DFGKER19D')
    '2023'
    """

    return ticket[YR: YR + 4]


# We provide the docstring for this function to help you get started.
def get_month(ticket: str) -> str:
    """Return the month of ticket 'ticket'.

    >>> get_month('20230915YYZYEG12F')
    '09'
    >>> get_month('20241215YYZYEG12F1236')
    '12'
    >>> get_month('20230926DFGKER19D')
    '09'
    """

    return ticket[MON: MON + 2]


# We provide the docstring for this function to help you get started.
def get_day(ticket: str) -> str:
    """Return the day of ticket 'ticket' in YYYYMMDD format.

    >>> get_day('20230915YYZYEG12F')
    '15'
    >>> get_day('20241215YYZYEG12F1236')
    '15'
    >>> get_day('20230926DFGKER19D')
    '26'
    """

    return ticket[DAY: DAY + 2]


def get_departure(ticket: str) -> str:
    """Return the departure location of ticket 'ticket'.

    >>> get_departure('20230915YYZYEG12F')
    'YYZ'
    >>> get_departure('20241215YYZYEG12F1236')
    'YYZ'
    >>> get_departure('20230926DFGKER19D')
    'DFG'
    """

    return ticket[DEP: DEP + 3]


def get_arrival(ticket: str) -> str:
    """Return the arrival location of ticket 'ticket'.

    >>> get_arrival('20230915YYZYEG12F')
    'YEG'
    >>> get_arrival('20241215YYZYEG12F1236')
    'YEG'
    >>> get_arrival('20230926DFGKER19D')
    'KER'
    """

    return ticket[ARR: ARR + 3]


def get_row(ticket: str) -> int:
    """Return the seat row of ticket 'ticket'.

    >>> get_row('20230915YYZYEG12F')
    12
    >>> get_row('20241215YYZYEG12F1236')
    12
    >>> get_row('20230926DFGKER19D')
    19
    """

    return int(ticket[ROW: ROW + 2])


def get_seat(ticket: str) -> str:
    """Return the seat type of ticket 'ticket'.

    >>> get_seat('20230915YYZYEG12F')
    'F'
    >>> get_seat('20241215YYZYEG12F1236')
    'F'
    >>> get_seat('20230926DFGKER19D')
    'D'
    """

    return ticket[SEAT: SEAT + 1]


def get_ffn(ticket: str) -> str:
    """Return the frequent flyer number (FFN) of ticket 'ticket'.
    If there is no FFN, an empty string '""' is returned.

    >>> get_ffn('20230915YYZYEG12F')
    ''
    >>> get_ffn('20241215YYZYEG12F1236')
    '1236'
    >>> get_ffn('20230926DFGKER19D')
    ''
    """

    return ticket[FFN: FFN + 4]


# """
# Task 2: Validating the Information (12 correctness marks)
# """
# We provide the docstring for this function to help you get started.
def is_valid_seat(ticket: str, first_row: int, last_row: int) -> bool:
    """Return True if and only if this ticket has a valid seat. That is,
    if the seat row is between 'first_row' and 'last_row', inclusive,
    and the seat is SA, SB, SC, SD, SE, or SF.
    Precondition: 'ticket' is in valid format.

    >>> is_valid_seat('20230915YYZYEG12F1236', 1, 30)
    True
    >>> is_valid_seat('20230915YYZYEG42F1236', 1, 30)
    False
    >>> is_valid_seat('20230915YYZYEG21Q1236', 1, 30)
    False
    """

    return (first_row <= get_row(ticket) <= last_row
            and get_seat(ticket) in (SA, SB, SC, SD, SE, SF))


def is_valid_ffn(ticket: str) -> bool:
    """
    The parameter takes a ticket 'ticket. The function should return True 
    if and only if the frequent flyer number (FFN) of this ticket is valid. For
    a ticket to be valid FFN, it must contain exactly four digits, and the 
    sum of the first three digits modulo 10 must be the same as the last 
    (fourth) digit. If an FFN doesn't exist, True is returned.
    Precondition: 'ticket' is in valid format.

    >>> is_valid_ffn('20230915YYZYEG12F1236')
    True
    >>> is_valid_ffn('20230915YYZYEG42F2468')
    False
    >>> is_valid_ffn('20230915YYZYEG42F')
    True
    >>> is_valid_ffn('20230915YYZYEG42F999')
    False
    """

    ffn = get_ffn(ticket)
    return (
        ffn == ""
        or ffn.isdigit()
        and len(ffn) == 4
        and sum(int(num) for num in ffn[:3]) % 10 == int(ffn[3])
    )


def is_leap_year(yr: int) -> bool:
    """
    Utility function to check for a leap year in year 'yr'
    Constraint: yr >= 0

    >>> is_leap_year(1000)
    False
    >>> is_leap_year(1996)
    True
    >>> is_leap_year(4000)
    True
    >>> is_leap_year(2100)
    False
    """

    return yr % 4 == 0 and (not yr % 100 == 0 or yr % 400 == 0)


def is_valid_date(ticket: str) -> bool:
    """
    The parameter represents the ticket. The function should return
    True if and only if the date of this ticket is valid.
    Constraints: 
    - Ticket must have be of form YYYYMMDD
    - year YYYY, month MM, and day DD must be defined integers in 
      string form

    >>> is_valid_date('20230915YYZYEG12F1236')
    True
    >>> is_valid_date('20290931YYZYEG42F')
    False
    >>> is_valid_date('20000231YYZYEG42F')
    False
    >>> is_valid_date('20000299YYZYEG42F') # date too high
    False
    >>> is_valid_date('20000229YYZYEG42F') # N00 leap year 29th
    True
    >>> is_valid_date('21040229YYZYEG42F') # regular leap year 29th
    True
    >>> is_valid_date('21000229YYZYEG42F') # N00 non leap year 29th
    False
    >>> is_valid_date('21000228YYZYEG42F') # N00 non leap year non 29th
    True
    """

    year = int(get_year(ticket))
    month = int(get_month(ticket))
    day = int(get_day(ticket))

    leap_year: bool = is_leap_year(year)
    return (
        1 <= month <= 12
        and (
            # months with 31 days
            month in {1, 3, 5, 7, 8, 10, 12} and 1 <= day <= 31
            # february and leap years
            or month == 2 and 1 <= day <= (28 + int(leap_year))
            # other
            or month != 2 and 1 <= day <= 30
        )
    )


def is_valid_ticket(ticket: str, first_row: int, last_row: int) -> bool:
    """
    The first parameter takes the ticket, 'ticket'. The second 'first_row' 
    parameter represents the number of the first row in the plane. The third 
    parameter 'last_row' represents the number of the last row in the plane. 
    The function should return True if and only if the ticket is in valid 
    format and all of the ticket information on this ticket is valid.

    >>> is_valid_ticket('20230915YYZYEG12F1236', 1, 20)
    True
    >>> is_valid_ticket('20230229YYZYEG12F1236', 1, 20)
    False
    >>> is_valid_ticket('20290931YYZYEG42F', 5, 30)
    False
    >>> is_valid_ticket('20000216YYZYEG42F', 9, 50)
    True
    >>> is_valid_ticket('20000216YYZYEG42Q', 9, 50)
    False
    """

    return (
        is_valid_ticket_format(ticket)
        and is_valid_date(ticket)
        and is_valid_seat(ticket, first_row, last_row)
        and is_valid_ffn(ticket)
    )


# We provide this function for you to use as a helper.
def is_valid_ticket_format(ticket: str) -> bool:
    """Return True if and only if ticket 'ticket' is in valid format:

    - year is 4 digits
    - months is 2 digits
    - day is 2 digits
    - departure is 3 letters
    - arrival is 3 letters
    - row is 2 digits
    - seat is a characters
    - frequent flyer number is either empty or 4 digits, and
      it is the last record in 'ticket'

    >>> is_valid_ticket_format('20241020YYZYEG12C1236')
    True
    >>> is_valid_ticket_format('20241020YYZYEG12C12361236')
    False
    >>> is_valid_ticket_format('ABC41020YYZYEG12C1236')
    False
    """

    return (FFN == 17
            and (len(ticket) == 17
                 or len(ticket) == 21 and ticket[FFN:FFN + 4].isdigit())
            and ticket[YR:YR + 4].isdigit()
            and ticket[MON:MON + 2].isdigit()
            and ticket[DAY:DAY + 2].isdigit()
            and ticket[DEP:DEP + 3].isalpha()
            and ticket[ARR:ARR + 3].isalpha()
            and ticket[ROW:ROW + 2].isdigit()
            and ticket[SEAT].isalpha())


# """
# Task 3: Analysing the Information (12 correctness marks)
# """
# We provide the docstring for this function to help you get started.
def visits_airport(ticket: str, airport: str) -> bool:
    """Return True if and only if either departure or arrival airport on
    ticket 'ticket' is the same as 'airport'.

    >>> visits_airport('20230915YYZYEG12F1236', 'YEG')
    True
    >>> visits_airport('20230915YEGYYZ12F1236', 'YEG')
    True
    >>> visits_airport('20230915YYZYEG12F1236', 'YVR')
    False
    """

    return (
        get_departure(ticket) == airport
        or get_arrival(ticket) == airport
    )


def connecting(ticket1: str, ticket2: str) -> bool:
    """
    The function should return True if and only if the two flights on
    'ticket1' and 'ticket2' respectively, are connecting: the first 
    flight arrives in the same airport as the departure point of the 
    second flight, and the two flights are on the same dates. 
    Constraints: 
    - The tickets are valid

    >>> connecting('20230915YYZYEG12F1236', '20230915YEGYYZ12F1236')
    True
    >>> connecting('20230915YYZYEG12F1236', '20230915YYZYEG12F1236')
    False
    >>> connecting('20230915AAABBB12F1236', '20230915BBBAAA12F1236')
    True
    >>> connecting('20230915BBBAAA12F1236', '20230915AAABBB12F1236')
    True
    >>> connecting('20230915AAABBB12F1236', '20230916BBBAAA12F1236')
    False
    """

    return (
        get_date(ticket1) == get_date(ticket2)
        and (
            get_arrival(ticket1) == get_departure(ticket2)
            or get_arrival(ticket2) == get_departure(ticket1)
        )
    )


# We provide the docstring for this function to help you get started.
def adjacent(ticket1: str, ticket2: str) -> bool:
    """Return True if any only if the seats in tickets 'ticket1' and
    'ticket2' are adjacent (next to each other). Seats across an aisle
    are not considered to be adjacent.
    Precondition: ticket1 and ticket2 are valid tickets.

    >>> adjacent('20230915YYZYEG12D1236', '20230915YYZYEG12E1236')
    True
    >>> adjacent('20230915YYZYEG12B1236', '20230915YYZYEG12A1236')
    True
    >>> adjacent('20230915YYZYEG12C1236', '20230915YYZYEG12D1236')
    False
    >>> adjacent('20230915YYZYEG12A1236', '20230915YYZYEG11B1236')
    False
    """

    seat1, seat2 = get_seat(ticket1), get_seat(ticket2)
    return (
        get_row(ticket1) == get_row(ticket2)
        and (
            (seat1 == SA and seat2 == SB)
            or (seat1 == SB and seat2 == SA)
            or (seat1 == SB and seat2 == SC)
            or (seat1 == SC and seat2 == SB)
            or (seat1 == SD and seat2 == SE)
            or (seat1 == SE and seat2 == SD)
            or (seat1 == SE and seat2 == SF)
            or (seat1 == SF and seat2 == SE)
        )
    )


def behind(ticket1: str, ticket2: str) -> bool:
    """
    The function should return True if and only if the seats on the 
    two tickets are one immediately behind another.
    Precondition: ticket1 and ticket2 are valid tickets.

    >>> behind('20230915YYZYEG12D1236', '20230915YYZYEG12E1236')
    False
    >>> behind('20230915YYZYEG12B1236', '20230915YYZYEG12A1236')
    False
    >>> behind('20230915YYZYEG12C1236', '20230915YYZYEG12D1236')
    False
    >>> behind('20230915YYZYEG12A1236', '20230915YYZYEG11B1236')
    False
    >>> behind('20230915YYZYEG12A1236', '20230915YYZYEG11A1236')
    True
    >>> behind('20230915YYZYEG11A1236', '20230915YYZYEG12A1236')
    True
    >>> behind('20230915YYZYEG11A1236', '20230915YYZYEG116A1236')
    False
    """

    row1, row2 = get_row(ticket1), get_row(ticket2)
    seat1, seat2 = get_seat(ticket1), get_seat(ticket2)
    return abs(row1 - row2) == 1 and seat1 == seat2


# We provide the docstring for this function to help you get started.
def get_seat_type(ticket: str) -> str:
    """Return WINDOW, AISLE, or MIDDLE depending on the type of seat in
    ticket 'ticket'.
    Precondition: 'ticket' is a valid ticket.

    >>> get_seat_type('20230915YYZYEG12F1236')
    'window'
    >>> get_seat_type('20230915YYZYEG08B')
    'middle'
    >>> get_seat_type('20230915YYZYEG12C1236')
    'aisle'
    """

    seat = get_seat(ticket)
    if seat == SA or seat == SF:
        return WINDOW
    if seat == SB or seat == SE:
        return MIDDLE
    return AISLE


# """
# Task 4: Changing the Information (BONUS 4 correctness marks)
# """
def change_seat(ticket: str, row_num: int, row_seat: str) -> str:
    """
    Returns a new ticket that is in the same format as the input ticket,
    has the same departure, arrival, date, and frequent flyer number as
    the input ticket, and has a new seat information with the given row
    and seat.
    Constraints:
    - 'ticket' is a valid ticket.
    - especially, new seat type should be valid ('A' - 'F')

    >>> change_seat('20230915YYZYEG12F1236', 44, 'C')
    '20230915YYZYEG44C1236'
    >>> change_seat('20230915YYZYEG08B', 45, 'D')
    '20230915YYZYEG45D'
    >>> change_seat('20230915YYZYEG12C1236', 28, 'F')
    '20230915YYZYEG28F1236'
    """

    return (
        get_date(ticket)
        + get_departure(ticket)
        + get_arrival(ticket)
        + str(row_num)
        + row_seat
        + get_ffn(ticket)
    )


def change_date(ticket: str, day: str, month: str, year: str) -> str:
    """
    Returns a new ticket that is in the same format as the input ticket, 
    has the same departure, arrival, seat information, and frequent flyer 
    number as the input ticket, and has a new date with year `year`, month
    `month`, and day `day`. Just like a regular ticket, the new ticket date
    is in YYYYMMDD format.
    Constraints:
    - 'ticket' is a valid ticket.

    >>> change_date('20230915YYZYEG12F1236', '09', '04', '2029')
    '20290409YYZYEG12F1236'
    >>> change_date('20230915YYZYEG08B', '14', '11', '1000')
    '10001114YYZYEG8B'
    >>> change_date('20230915YYZYEG12C1236', '30', '09', '2001')
    '20010930YYZYEG12C1236'
    """

    return (
        year
        + month
        + day
        + get_departure(ticket)
        + get_arrival(ticket)
        + str(get_row(ticket))
        + get_seat(ticket)
        + get_ffn(ticket)
    )


if __name__ == '__main__':
    import doctest
    doctest.testmod()
