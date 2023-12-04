"""CSCA08 Assignment 3: arxiv.org

This code is provided solely for the personal and private use of
students taking the CSCA08 course at the University of
Toronto. Copying for purposes other than this use is expressly
prohibited. All forms of distribution of this code, whether as given
or with any changes, are expressly prohibited.

All of the files in this directory and all subdirectories are:
Copyright (c) 2021-2023 Anya Tafliovich.

"""

import copy  # needed in examples of functions that modify input dict
from typing import TextIO

# remove unused constants from this import statement when you are
# finished your assignment
from constants import (ID, TITLE, CREATED, MODIFIED, AUTHORS,
                       ABSTRACT, END, SEPARATOR, NameType,
                       ArticleValueType, ArticleType, ArxivType)

EXAMPLE_ARXIV = {
    '008': {
        'identifier': '008',
        'title': 'Intro to CS is the best course ever',
        'created': '2021-09-01',
        'modified': None,
        'authors': [('Ponce', 'Marcelo'), ('Tafliovich', 'Anya Y.')],
        'abstract': '''We present clear evidence that Introduction to
Computer Science is the best course.'''},
    '031': {
        'identifier': '031',
        'title': 'Calculus is the best course ever',
        'created': None,
        'modified': '2021-09-02',
        'authors': [('Breuss', 'Nataliya')],
        'abstract': '''We discuss the reasons why Calculus I
is the best course.'''},
    '067': {'identifier': '067',
            'title': 'Discrete Mathematics is the best course ever',
            'created': '2021-09-02',
            'modified': '2021-10-01',
            'authors': [('Bretscher', 'Anna'), ('Pancer', 'Richard')],
            'abstract': ('We explain why Discrete Mathematics is the best ' +
                         'course of all times.')},
    '827': {
        'identifier': '827',
        'title': 'University of Toronto is the best university',
        'created': '2021-08-20',
        'modified': '2021-10-02',
        'authors': [('Bretscher', 'Anna'),
                    ('Ponce', 'Marcelo'),
                    ('Tafliovich', 'Anya Y.')],
        'abstract': '''We show a formal proof that the University of
Toronto is the best university.'''},
    '042': {
        'identifier': '042',
        'title': None,
        'created': '2021-05-04',
        'modified': '2021-05-05',
        'authors': [],
        'abstract': '''This is a very strange article with no title
and no authors.'''}
}
# print(EXAMPLE_ARXIV)

EXAMPLE_BY_AUTHOR = {
    ('Ponce', 'Marcelo'): ['008', '827'],
    ('Tafliovich', 'Anya Y.'): ['008', '827'],
    ('Bretscher', 'Anna'): ['067', '827'],
    ('Breuss', 'Nataliya'): ['031'],
    ('Pancer', 'Richard'): ['067']
}


# We provide the header and part of a docstring for this function to
# get you started and to demonstrate the use of example data.
def make_author_to_articles(
        id_to_article: ArxivType) -> dict[NameType, list[str]]:
    """Return a dict that maps each author name to a list (sorted in
    lexicographic order) of IDs of articles written by that author,
    based on the information in arxiv data id_to_article.

    >>> make_author_to_articles(EXAMPLE_ARXIV) == EXAMPLE_BY_AUTHOR
    True
    >>> make_author_to_articles({'gg': EXAMPLE_ARXIV['042']})
    {}
    """

    author_to_articles = {}

    for article_id in id_to_article:
        for author in id_to_article[article_id]['authors']:
            if author not in author_to_articles:
                author_to_articles[author] = []
            author_to_articles[author].append(article_id)

    return author_to_articles


def get_coauthors(id_to_article: ArxivType,
                  author_name: NameType) -> list[NameType]:
    """
    Returns a list of coauthors of the author specified by the second argument.
    (Two people are coauthors if they are authors of the same article.) The
    list should be sorted in lexicographic order.

    >>> get_coauthors(EXAMPLE_ARXIV, ('Tafliovich', 'Anya Y.'))
    [('Bretscher', 'Anna'), ('Ponce', 'Marcelo')]
    >>> get_coauthors({'gg': EXAMPLE_ARXIV['042']}, ('Tafliovich, Anya Y.'))
    []
    """

    coauthors = set()
    for article_id in id_to_article:
        article = id_to_article[article_id]
        if author_name not in article['authors']:
            continue

        for author in article['authors']:
            if author != author_name:
                coauthors.add(author)

    return sorted(list(coauthors))


def get_most_published_authors(id_to_article: ArxivType) -> list[NameType]:
    """
    Returns a list of authors who published the most articles.
    Note that this list has more than one author only in case of a tie

    >>> get_most_published_authors(EXAMPLE_ARXIV)
    [('Bretscher', 'Anna'), ('Ponce', 'Marcelo'), ('Tafliovich', 'Anya Y.')]
    >>> get_most_published_authors({'gg': EXAMPLE_ARXIV['008']})
    [('Ponce', 'Marcelo'), ('Tafliovich', 'Anya Y.')]
    >>> get_most_published_authors({'gg': EXAMPLE_ARXIV['031']})
    [('Breuss', 'Nataliya')]
    >>> get_most_published_authors({'gg': EXAMPLE_ARXIV['042']})
    []
    """

    most_published = []
    most_pubs = 0

    author_to_articles = make_author_to_articles(id_to_article)
    for author, articles in author_to_articles.items():
        if len(articles) == most_pubs:
            most_published.append(author)
        elif len(articles) > most_pubs:
            most_published = [author]
            most_pubs = len(articles)

    return sorted(most_published)


def suggest_collaborators(id_to_article: ArxivType,
                          author_name: NameType) -> list[NameType]:
    """
    Returns a list of authors with whom the author specified by the second
    argument is encouraged to collaborate. The list should be sorted in
    lexicographic order.

    The list of suggested collaborators should include all authors who are
    coauthors of this author's coauthors. In other words, if author A wrote
    an article with author B and author B wrote an article with author C,
    then we will include C as suggested collaborator for A.

    >>> suggest_collaborators(EXAMPLE_ARXIV, ('Pancer', 'Richard'))
    [('Ponce', 'Marcelo'), ('Tafliovich', 'Anya Y.')]
    >>> suggest_collaborators(EXAMPLE_ARXIV, ('Tafliovich', 'Anya Y.'))
    [('Pancer', 'Richard')]
    >>> suggest_collaborators(EXAMPLE_ARXIV, ('g', 'g'))
    []
    """

    coauthors = get_coauthors(id_to_article, author_name)
    suggested_collaborators = set()

    for coauthor in coauthors:
        for cocoauthor in get_coauthors(id_to_article, coauthor):
            if cocoauthor != author_name and cocoauthor not in coauthors:
                suggested_collaborators.add(cocoauthor)

    return sorted(list(suggested_collaborators))


def has_prolific_authors(author_to_ids: dict[NameType, list[str]],
                         article: ArticleType,
                         prolific_threshold: int) -> bool:
    """
    Returns True if and only if the article (second argument) has at least
    one author who is considered prolific.

    >>> has_prolific_authors(EXAMPLE_BY_AUTHOR, EXAMPLE_ARXIV['008'], 2)
    True
    >>> has_prolific_authors(EXAMPLE_BY_AUTHOR, EXAMPLE_ARXIV['031'], 2)
    False
    """

    for author in article['authors']:
        if len(author_to_ids[author]) >= prolific_threshold:
            return True

    return False


# We provide the header and part of a docstring for this function to
# get you started and to demonstrate the use of function deepcopy in
# examples that modify input data.
def keep_prolific_authors(id_to_article: ArxivType,
                          min_publications: int) -> None:
    """Update the articles data id_to_article so that it contains only
    articles published by authors with min_publications or more
    articles published. As long as at least one of the authors has
    min_publications, the article is kept.

    >>> arxiv_copy = copy.deepcopy(EXAMPLE_ARXIV)
    >>> keep_prolific_authors(arxiv_copy, 2)
    >>> len(arxiv_copy)
    3
    >>> '008' in arxiv_copy and '067' in arxiv_copy and '827' in arxiv_copy
    True
    """

    id_to_article_copy = copy.deepcopy(id_to_article)

    for article_id in id_to_article_copy:
        if not has_prolific_authors(
            make_author_to_articles(id_to_article),
            id_to_article[article_id],
            min_publications
        ):
            del id_to_article[article_id]


# We provide the header and docstring for this function to get you
# started and to demonstrate that there are no docstring examples in
# functions that read from files.
def read_arxiv_file(afile: TextIO) -> ArxivType:
    """Return a dict containing all arxiv information in afile.
    Precondition: afile is open for reading
                  afile is in the format described in the handout
    """

    raw_books = afile.read().split(END)[: -1]

    books = {}
    for raw_book in raw_books:
        book = {}
        meta_info = raw_book.strip().split("\n")
        # print(meta_info)

        book[ID] = meta_info[0] if meta_info[0] != '' else None
        book[TITLE] = meta_info[1] if meta_info[1] != '' else None
        book[CREATED] = meta_info[2] if meta_info[2] != '' else None
        book[MODIFIED] = meta_info[3] if meta_info[3] != '' else None

        passed_nulls = 0
        for i in range(4, len(meta_info)):
            if meta_info[i] == '':
                if i == 4:
                    book[AUTHORS] = []

                passed_nulls += 1
                continue

            match passed_nulls:
                case 0:
                    book[AUTHORS] = book.get(
                        AUTHORS, []) + [tuple(meta_info[i].split(SEPARATOR))]
                    book[AUTHORS] = sorted(book[AUTHORS])
                case 1:
                    book[ABSTRACT] = (book.get(ABSTRACT, '') +
                                      '\n' + meta_info[i]).strip()

        books[book[ID]] = book

    # print(books)
    return books


if __name__ == '__main__':
    import doctest
    doctest.testmod()

    # uncomment to test with example data files
    with open('example_data.txt', encoding='utf-8') as example_data:
        RESULT = read_arxiv_file(example_data)
        print('Did we produce a correct dict? ',
              RESULT == EXAMPLE_ARXIV)

    # uncomment to work with a larger data set
    with open('data.txt', encoding='utf-8') as data_txt:
        EXAMPLE = read_arxiv_file(data_txt)

    # EXAMPLE_AUTHOR_TO_ARTICLE = make_author_to_articles(EXAMPLE)
    # EXAMPLE_MOST_PUBLISHED = get_most_published_authors(EXAMPLE)
    # print(EXAMPLE_MOST_PUBLISHED)
    # print(get_coauthors(EXAMPLE, ('Varanasi', 'Mahesh K.')))  # one
    # print(get_coauthors(EXAMPLE, ('Chablat', 'Damien')))  # many
