from typing import NamedTuple
import shutil
import glob
import os


class Code(NamedTuple):
    name: str
    file: str
    extension: str


def goToParent():
    os.chdir(os.path.dirname(os.getcwd()))


def searchFile(filename):
    # Find all files: "filename.*"

    def valid(file):
        extension = os.path.splitext(file)[1]
        return len(extension) > 0 and not extension.endswith(".out")

    result = [file for file in glob.glob(f"{filename}.*") if valid(file)]

    if len(result) == 0:
        print(f"{filename} not found")
        exit()

    if len(result) > 1:
        print(
            f"There are {len(result)} files which match '{filename}.*', please change the name to something unique :)")
        exit()

    return result[0]


def readFileName(query):
    # Read solution name
    print(f"{query}: ", end="")
    file = searchFile(input())
    # name, file, extension
    return Code(os.path.splitext(file)[0], file, os.path.splitext(file)[1])


def createFolder(name):
    # Create folder
    folderName = f"Problem-{name}"
    if os.path.exists(folderName):
        shutil.rmtree(folderName)
    os.mkdir(folderName)
    return folderName


def readTestCases():
    print("Insert the number of subtasks: ", end="")
    subtasks = int(input())
    print("Write down the number of test-cases per subtask")

    testCases = []
    percentage = []
    for i in range(0, subtasks):
        print(f"Subtask {i+1}: ", end="")
        testCases.append(int(input()))
        # percentage.append()

    return testCases


def addStatements(testCases):
    os.mkdir("statements")
    os.chdir("statements")

    markdown = open("es.markdown", 'a')

    markdown.write("# Descripción\n")
    markdown.write(" Historia del problema\n\n")
    markdown.write("# Entrada\n Variables en `rojo`, solo $texto$\n\n")
    markdown.write("# Salida\n ¿qué queremos de salida?\n\n")
    markdown.write("# Ejemplo\n")
    markdown.write("|| input\n || output\n || description\n || end\n\n")
    markdown.write("|| input\n || output\n || description\n || end\n\n")

    markdown.write("# Límites\n\n")
    markdown.write("- $1 \leq n \leq 10^5$")
    markdown.write("\n\n----------\n\n")

    if len(testCases) >= 2:
        markdown.write("# Subtareas\n\n")

        totalCases = 0
        for numCases in testCases:
            totalCases += numCases

        for pos, numCases in enumerate(testCases):
            percentage = numCases * 100 / totalCases
            if pos + 1 < len(testCases):
                markdown.write(f"Para un {percentage} % de los casos:\n\n")
                markdown.write("- $1 \leq n \leq 10$\n")
                markdown.write("\n\n----------\n\n")
            else:
                markdown.write(
                    f"Para el {percentage} % de los casos restantes, los límites originales.")

    markdown.close()
    goToParent()


def generateTestCases(solution, generator, testCases):
    def compileIfNeeded(code):
        if code.extension == ".cpp":
            os.system(f"g++ --std=c++17 {code.file} -o {code.name}.out")

    os.mkdir("cases")

    compileIfNeeded(solution)
    compileIfNeeded(generator)

    def runCase(name, level):
        inputFile = f"cases/{name}.in"
        outputFile = f"cases/{name}.out"

        trash = open("trash", 'w')
        trash.write(f"{level}")
        trash.close()

        if generator[2] == ".cpp":
            os.system(f"./{generator.name}.out < trash > {inputFile}")
        else:
            os.system(f"python3 {generator.file} < trash > {inputFile}")

        if solution[2] == ".cpp":
            os.system(f"./{solution.name}.out < {inputFile} > {outputFile}")
        else:
            os.system(f"python3 {solution.file} < {inputFile} > {outputFile}")

    if len(testCases) == 0:
        testCases = [25]

    sumCases = 0
    for level, numTestCases in enumerate(testCases):
        for it in range(0, numTestCases):
            # For grouped cases set name to f"{level + 1}.{it}"
            # For ungrouped cases set name to sumCases
            runCase(f"{sumCases}", level)
            sumCases += 1


def moveFiles(files, path, keep=True):
    for file in files:
        shutil.copyfile(file, os.path.join(path, file))
        if keep == False:
            os.system(f"rm {file}")


def generateZip(folder):
    print("Select a name for the zip: ", end="")
    problemName = input()
    os.system(f"zip -r {problemName}.zip {folder}")


def main():
    whereIAm = os.getcwd()
    solution = readFileName("Solution")
    generator = readFileName("Test-case generator")
    folder = createFolder(solution.name)

    moveFiles([solution.file, generator.file], folder)

    # Change directory
    os.chdir(folder)

    # testCases can be replaced with an array
    testCases = readTestCases()  # [4, 5] (2 subtasks)
    addStatements(testCases)
    generateTestCases(solution, generator, testCases)

    os.mkdir("solutions")
    moveFiles([solution.file, generator.file], "solutions", False)

    os.chdir(whereIAm)
    generateZip(folder)

    print("Ready to omegaup")


if __name__ == "__main__":
    main()
