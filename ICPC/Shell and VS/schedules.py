import requests
import pprint
from bs4 import BeautifulSoup
from tabulate import tabulate
import pandas as pd
import json

def filterByPreferredNRC(allCourses, preferredNRC):
  # Remove all NRC which are NOT in preffered NRC for a certain key
  for key, courses in allCourses.items():
    if key in preferredNRC:
      newCourses = []
      for course in courses:
        if course['nrc'] in preferredNRC[key] or len(course['virtual']) > 0:
          newCourses.append(course)
      allCourses[key] = newCourses

  return allCourses

def groupBySameKey(courses):
  same = dict()
  for subject in courses:
    key = subject['key']
    subject.pop('key')
    
    if key not in same:
      same[key] = []
    same[key].append(subject)
    
  return same

def getCourses(year, coursesKeysSet, ignoreNRC, virtualCourses):
  career = 'INCO'
  url = f'http://consulta.siiau.udg.mx/wco/sspseca.consulta_oferta?ciclop={year}&cup=D&majrp=INCO&crsep=&materiap=&horaip=&horafp=&edifp=&aulap=&ordenp=0&mostrarp=1000'
  
  r = requests.get(url)
  soup = BeautifulSoup(r.text, 'html.parser')
  
  coursesList = []
  for tr in soup.find_all('tr')[2:-2]:
    data = tr.text.splitlines()
    if len(data) >= 18:
      # Materias con más de un horario
      h = len(data) - 18

      course = {
        'nrc': data[1],
        'key': data[2],
        'subject': data[3].capitalize(),
        'section': data[4],
        'credits': data[5],
        'total': data[6],
        'available': data[7],
        'teacher': data[h + 16].title(),
        'virtual': ""
      }
      
      if course['key'] not in coursesKeysSet:
        continue

      if course['nrc'] in ignoreNRC:
        continue

      if course['nrc'] in virtualCourses:
        course['virtual'] = " (Virtual)"

      days = []
      for i in range(h + 1):
        start = data[i + 11][2:6]
        end = data[i + 11][7:11]
        
        whichDays = []
        for day in data[i + 11][11:22]:
          if day.isalpha():
            whichDays.append(day)
            
        # Alpha y Beta
        isDuct = 0
        if data[i + 11][22:26] == 'DUCT':
          isDuct = 1

        building = data[i + 11][22 : 26 + isDuct]
        classroom = data[i + 11][26 + isDuct : 30 + isDuct]
        
        for day in whichDays:
          days.append({
            'start': int(start),
            'end': int(end),
            'day': day,
            'building': building,
            'classroom': classroom
          })
        
      course.update({'days': days})

      coursesList.append(course)

  # with open(career + '.json', 'w') as file:
  #   json.dump(coursesList, file, sort_keys=False, indent=4)

  return groupBySameKey(coursesList)

def generateSchedules(coursesKeys, courses, preferred):
  schedules = []
  
  def getKey(day):
    return frozenset({
      'start': day['start'],
      'end': day['end'],
      'day': day['day']
    }.items()) 

  def dfs(pos, currentSchedule):
    if pos == len(coursesKeys):
      schedules.append(currentSchedule.copy())
      return

    courseKey = coursesKeys[pos]
    if courseKey not in courses:
      dfs(pos + 1, currentSchedule)
      return
      
    for course in courses[courseKey]:
      def updateSchedule(days, operation):
        # Add/Remove this days from the current schedule
        for day in days:
          dayKey = getKey(day)
          if operation == +1:
            courseCopy = course.copy()
            courseCopy.update({'key': courseKey})
            currentSchedule[dayKey] = courseCopy
          else:
            if dayKey in currentSchedule:
              currentSchedule.pop(dayKey)
        
      def valid(days): 
        # Check if we can append this days to the 'current' schedule
        for day in days:
          if preferred['start'] <= day['start'] and day['end'] <= preferred['end']:
            if day['day'] not in preferred['days']:
              return False      
            if getKey(day) in currentSchedule.keys():
              return False   
          else:
            return False   
        
        return True  
      
      if valid(course['days']):
        updateSchedule(course['days'], +1)
        dfs(pos + 1, currentSchedule)
        updateSchedule(course['days'], -1)
    return
  
  currentSchedule = dict()
  dfs(0, currentSchedule)
  return schedules

def prettySchedule(schedule):
  day = [["" for i in range(7)] for i in range(15)]
  
  day[0] = ["", "L", "M", "I", "J", "V", "S"]
  for i, hour in enumerate(range(7, 21)):
    day[i + 1][0] = str(hour) + ":00"
  
  info = dict()
  for key, data in schedule.items():
    key = dict(key)
    info[data['nrc']] = {
      'key': data['key'], 
      'teacher': data['teacher'], 
      'subject': data['subject'],
      'virtual': data['virtual'],
    }
    
    weekDay = 0
    while weekDay < len(day[0]):
      if day[0][weekDay] == key['day']:
        break
      weekDay += 1

    start = key['start'] // 100
    end = key['end'] // 100

    for i in range(start, end + 1):
      day[i - 6][weekDay] = data['nrc'] + data['virtual']
  
  print(tabulate(day, tablefmt='fancy_grid'))
  print(tabulate(pd.DataFrame(info).T, headers="keys"))

if __name__ == '__main__':
  # Year to select
  year = "202210"
  # Courses to take
  coursesKeysSet = {"I7029", "I7027", "I7038", "I7039", "I7030", "I7036"}
  # NRC's to ignore
  ignoreNRC = {"153405", "164138", "179961"}
  # Preferred time range and days
  preferred = {
    'start': 700,
    'end': 1600,
    'days': "LMIJV",
  }

  virtualCourses = {"119905", "119906", "103848", "130032", "103860", "103861", "103844", "103845", "119896","92948", "103856"}
  courses = getCourses(year, coursesKeysSet, ignoreNRC, virtualCourses)

  preferredNRC = {
    "I7039": ["119908", "179959"],
    "I7035": ["124889"],
    "I7027": ["131871", "131872", "164160"],
    "I7038": ["103847", "174378"],
  }
  courses = filterByPreferredNRC(courses, preferredNRC)

  schedules = generateSchedules(list(coursesKeysSet), courses, preferred)
  
  for pos, schedule in enumerate(schedules):
    print(f"{pos + 1} / {len(schedules)}")
    prettySchedule(schedule)
    print()
  
