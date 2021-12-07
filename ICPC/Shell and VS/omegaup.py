import shutil
import glob
import os

def main():
  def goToParent():
    os.chdir(os.path.dirname(os.getcwd()))  

  def searchFile(filename):
    # Find all files: "filename.*"
    result = glob.glob("{}.*".format(filename))
    
    if len(result) == 0:
      print("{} not found".format(filename))
      exit()

    if len(result) > 1:
      print("There are {} files which match '{}.*', please change the name to something unique :)".format(len(result), filename))
      exit()

    return result[0]

  def toNameFileExtension(file):  
    # name, file, extension
    return [os.path.splitext(file)[0], file, os.path.splitext(file)[1]]

  def readFileName(query): 
    # Read solution name
    print("{}: ".format(query), end = "")
    file = searchFile(input())
    return toNameFileExtension(file)

  def createFolder(name):
    # Create folder
    folderName = "Problem-{}".format(name)
    if os.path.exists(folderName):
      shutil.rmtree(folderName)
    os.mkdir(folderName)
    return folderName

  def copyFile(file, path):
    return shutil.copyfile(file, os.path.join(path, file))

  def readTestCases():
    print("Insert the number of subtasks: ", end = "")
    subtasks = int(input())
    print("Write down the number of test-cases per subtask: ")
    return [int(input()) for i in range(0, subtasks)]

  def addStatements(testCases):
    os.mkdir("statements")
    os.chdir("statements")

    markdown = open("es.markdown", 'a')

    markdown.write("# Descripción\n")
    markdown.write(" Historia del problema\n")
    markdown.write("# Entrada\n Variables en `rojo`, solo $texto$\n")
    markdown.write("# Salida\n ¿qué queremos de salida?\n")
    markdown.write("# Ejemplo\n || input\n || output\n || description \n || end\n")

    markdown.write("# Límites\n")
    markdown.write("- \$1 \leq n \leq 10^5$")
    markdown.write("\n----------\n")

    if len(testCases) >= 2:
      markdown.write("# Subtareas\n")

      totalCases = 0
      for numCases in testCases:
        totalCases += numCases

      for pos, numCases in enumerate(testCases):
        percentage = numCases * 100 / totalCases
        if pos + 1 < len(testCases):
          markdown.write("Para un {} % de los casos:\n".format(percentage))
          markdown.write("- $1 \leq n \leq 10$\n")
          markdown.write("\n----------\n")
        else:
          markdown.write("Para el {} % de los casos restantes, los límites originales.".format(percentage))

    markdown.close()
    goToParent()

  def generateTestCases(solution, generator, testCases):
    def compileIfNeeded(file):
      if file[2] == ".cpp":
        os.system("g++-11 --std=c++17 {} -o {}.out".format(file[1], file[0]))
  
    os.mkdir("cases")

    compileIfNeeded(solution)
    compileIfNeeded(generator)

    def run(testName, generatorType):
      inputFile = "cases/{}.in".format(testName)
      outputFile = "cases/{}.out".format(testName)

      trash = open("trash", 'w')
      trash.write("{}".format(generatorType))
      trash.close()
      
      if generator[2] == ".cpp":
        os.system("./{}.out < trash > {}".format(generator[0], inputFile))
      else:
        os.system("python3 {} < trash > {}".format(generator[1], inputFile))

      if solution[2] == ".cpp":
        os.system("./{}.out < {} > {}".format(solution[0], inputFile, outputFile))
      else:
        os.system("python3 {} < {} > {}".format(solution[1], inputFile, outputFile))

    if len(testCases) == 0:
      for i in range(0, 25):
        run(i, i)
    else:
      for i, numCases in enumerate(testCases):
        for j in range(0, numCases):
          testName = j if i == 0 else "subtask{}.{}".format(i, j)
          run(testName, i)

    goToParent()

  whereIAm = os.getcwd()
  solution = readFileName("Solution")
  generator = readFileName("Test-case generator")
  folder = createFolder(solution[0])

  copyFile(solution[1], folder)
  copyFile(generator[1], folder)

  # Change directory
  os.chdir(folder) 

  testCases = readTestCases()
  addStatements(testCases)
  generateTestCases(solution, generator, testCases)

  print("Ready to omegaup")

if __name__ == "__main__":
  main()