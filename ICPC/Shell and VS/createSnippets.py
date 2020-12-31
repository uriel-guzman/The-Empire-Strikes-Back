import os


def solve(file, dir, out):
  # print(file, dir)
  cppFile = open(dir, "r")

  name = file[:-4]
  # print(name)

  out.write("  \"{}\": {{\n".format(name))
  out.write("    \"prefix\": \"{}\",\n".format(name))
  out.write("    \"body\": [\n")
  for line in cppFile:
    if line.endswith("\n"):
      line = line[:-1]
    out.write("    \"{}\",\n".format(line))
  out.write("    ],\n")
  out.write("    \"description:\" \"{}\"\n".format(file))  
  out.write("  },\n")

def main():
  print("Create snippets")
  rootdir = r'/Users/abraham/The-Empire-Strikes-Back/ICPC/Codes/'

  out = open("/Users/abraham/Library/Application Support/Code/User/snippets/cpp.json", "w")
  out.write("{\n")

  for subdir, dirs, files in os.walk(rootdir):
      if subdir.endswith("Misc"): 
        continue

      for file in files:
          #print os.path.join(subdir, file)
          filepath = subdir + os.sep + file

          if filepath.endswith(".cpp"):
            solve(file, filepath, out)

  out.write("}\n")
  out.close()

            
if __name__ == "__main__":
    main()