import glob
import os

# Only MacOS users, sorry :(
icpcPath = "/Users/*/*/ICPC/Codes/"
cppJsonPath = "/Users/*/Library/Application Support/Code/User/snippets/cpp.json"

def solve(file, pathToFile, out):
  cppFile = open(pathToFile, "r")

  name = file[:-4]

  out.write("  \"{}\": {{\n".format(name))
  out.write("    \"prefix\": \"{}\",\n".format(name))

  def getBody(cppFile): 
    codeByLines = list()
    for line in cppFile: 
      printableLine = str("")

      for ch in line: 
        if ch == '\\' or ch == '\$' or ch == '\"':
          printableLine += '\\' # special dummy characters
        printableLine += ch
      
      if line.endswith("\n"):
        printableLine = printableLine[:-1]
      codeByLines.append(printableLine)
      
    return codeByLines

  out.write("    \"body\": [\n")
  for line in getBody(cppFile):
    out.write("    \"{}\",\n".format(line))
  out.write("    ],\n")

  out.write("    \"description:\" \"{}\"\n".format(file))  
  out.write("  },\n")

def main():
  cppJson = glob.glob(cppJsonPath, recursive=True)[0]
    
  if os.path.isfile(cppJson) == False:
    print("Wtf!, you don't have cpp's snippets for vscode")
    return

  out = open(cppJson, "w")
  out.write("{\n")

  icpc = glob.glob(icpcPath, recursive=True)[0]
  if os.path.isdir(icpc) == False:
    print("Wtf!, where is the ICPC repository?")
    return
  
  for path, directories, files in os.walk(icpc):
    for file in files:
      pathToFile = path + os.sep + file

      if file.endswith(".cpp"):
        solve(file, pathToFile, out)

  out.write("}\n")
  out.close()
  print("Snippets up to date.")
            
if __name__ == "__main__":
  main()