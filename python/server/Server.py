#!/usr/bin/python
import socket
from flask import Flask
from flask import send_file,render_template
import threading
import os
import datetime

class Server(threading.Thread):
    def __init__(self, directoryToParse):
        self.observs = []
        threading.Thread.__init__(self)
        self.app = Flask(__name__)
        self.directory = directoryToParse

        @self.app.route('/')
        def observations():
          # For now, rebuild observations directory each time
          self.observs = []
          for filename in os.listdir(self.directory):
            if filename.endswith(".jpg"):
              self.observs.append({"filename":filename, "date_string":self.extract_date_from_filename(filename)})
            else:
              pass
          self.observs.sort(reverse=False, key=self.sorting)
          return render_template('observations.html', observs=self.observs)

        @self.app.route('/static/<filename>')
        def file(filename):
            file = self.directory + filename
            print(file)
            try:
                return send_file(file)
            except:
                return "Image outdated"
        @self.app.route('/take')
        def take_pic():
            cap = cv.VideoCapture(0)
            cap.set(3,1280)
            cap.set(4,1024)
            ret,frame = cap.read()
            cv.imwrite('image.png',frame)
            cap.release()
            return "took image"

    def run(self):
        self.app.run(host='0.0.0.0', threaded=True)

    def sorting(self, entry):
      index = entry["filename"].find('_');
      if (index < 0):
        print("Cannot parse file")
        return -1
      else:
        date_float = int(entry["filename"][:index]) / 1000.0
        return date_float

    def extract_date_from_filename(self, filename):
      index = filename.find('_');
      if (index < 0):
        print("Cannot parse file")
        return -1
      else:
        date_float = int(filename[:index]) / 1000.0
        return datetime.datetime.fromtimestamp(date_float).strftime('%Y-%m-%d %H:%M:%S.%f')
