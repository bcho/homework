from __future__ import print_function

import requests
import pandas as pd
from zipfile import ZipFile
from StringIO import StringIO


zipball = 'http://seanlahman.com/files/database/lahman-csv_2014-02-14.zip'
local_zipball = 'lahman-csv_2014-02-14.zip'


def retrieve_zipball(zipball_url):
    '''Retrieve the zipball data.'''
    resp = requests.get(zipball_url)
    resp.raise_for_status()
    return ZipFile(StringIO(resp.text))


def retrieve_local_zipball(zipball_path):
    '''Retrieve the zipball data from local.'''
    return ZipFile(open(zipball_path))


lahman_data = retrieve_local_zipball(local_zipball)
csv_salaries = pd.read_csv(lahman_data.open('Salaries.csv'))
csv_teams = pd.read_csv(lahman_data.open('Teams.csv'))


# Problem 1a:
print(csv_salaries.head())
print(csv_teams.head())


# Problem 1b:
salaries_by_team_year = csv_salaries.groupby(['teamID', 'yearID'],
                                             as_index=False).sum()
print(salaries_by_team_year.head())


# Problem 1c:
teams_and_salaries = csv_teams.merge(salaries_by_team_year,
                                     on=['teamID', 'yearID'])
grouped_by_team_year = teams_and_salaries.groupby(['teamID', 'yearID'],
                                                  as_index=False).sum()
print(grouped_by_team_year[['W', 'salary']].head())
