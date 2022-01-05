import glob
import os

# Only MacOS users, sorry :(
icpcPath = "/Users/*/*/ICPC/Codes/"

def main():
  icpc = glob.glob(icpcPath, recursive=True)[0]
  if os.path.isdir(icpc) == False:
    print("Wtf!, where is the ICPC repository?")
    return

  def addSpecialCharacters(str):
    special=""
    for ch in str:
      if ch == '\\' or ch == '\$' or ch == '\"' or ch == ' ':
        special += '\\' # special dummy character
      special += ch
    return special

  for path, directories, files in os.walk(icpc):
    for file in files:
      pathToFile = path + os.sep + file

      if file.endswith(".cpp") or file.endswith(".h"):
        os.system("clang-format --verbose -i --style=file {}".format(addSpecialCharacters(pathToFile)))

  print("\nAll files at {} clang-formatted".format(icpc))

if __name__ == "__main__":
  main()