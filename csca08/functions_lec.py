"""Code for week 2 worksheets: starter code.
"""


from math import ceil


def add_bonus(grade: float, bonus: float) -> float:
    """Return the result of adding bonus to grade, capped at 100.0.

    >>> add_bonus(67.0, 10.0)
    77.0
    >>> add_bonus(92.5, 9.0)
    100.0
    """

    return min(grade + bonus, 100.0)


def percentage(num: int, out_of: int) -> int:
    """Return what percent num is of out_of, rounded to an int
    (using the function round for rounding).

    >>> percentage(10, 200)
    5
    >>> percentage(151, 300)
    50
    """

    return round(num / out_of * 100)


# def max_of_min(num1: float, num2: float, val1: float, val2: float) -> float:
#     """Return the maximum of the minimums of the pairs num1 and num2,
#     and val1 and val2.

#     >>> max_of_min(4.0, 3.7)
#     ???
#     >>> ???
#     ???
#     """

#     return max(min(num1, num2), min(val1, val2))


"""Code for week 2 worksheets: starter code.
"""

# Note: We use the function ceil ("ceiling") to round up to the
# nearest integer: for example, ceil(3.14) evaluates to 4.
# Bad description: Return the number of boxes needed to store pencils.


def number_of_boxes(num_pencils: int, pencils_per_box: int) -> int:
    """
    Return the minimum number of boxes needed to store num_pencils pencils
    if every box can store pencils_per_box pencils.

    Constraints:
    - num_pencils > 0
    - pencils_per_box > 0


    >>> number_of_boxes(200, 10)
    20
    >>> number_of_boxes(206, 10)
    21
    """

    return ceil(num_pencils / pencils_per_box)


"""
2. Following the Function Design Recipe, write the following function.
Function name: (parameter types) → return type
calculate total: (float, float) → float
Description (need to change for the docstring!)
The first parameter represents a bill and the second represents a tax rate (a number between 0.0
and 1.0 inclusive). The function should return the total amount to be paid on the given bill.
"""

def 

if __name__ == '__main__':
    import doctest
    doctest.testmod()
