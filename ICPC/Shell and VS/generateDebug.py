from pprint import pprint

filename = input()
file = open(filename)
lines = file.readlines()
file.close()

debug = open("debug.h", "r")
header = debug.readline()
debug.close()

debug = open("debug.h", "w")
debug.write(header)


def removeDefaultValues(line):
    newLine = ""
    ignore = False
    balance = 0
    for ch in line:
        balance += (ch == '{' or ch == '(' or ch == '<')
        balance -= (ch == '}' or ch == ')' or ch == '>')
        if ch == '=':
            ignore = True
        elif ignore:
            if (ch == ',' or ch == ';') and balance == 0:
                ignore = False
        else:
            newLine += ch
    return newLine


def removePointers(line):
    newLine = ""
    ignore = False
    for ch in line:
        if ch == '*':
            ignore = True
        elif ignore:
            if ch == ',' or ch == ';':
                ignore = False
        else:
            if not (ch == ',' or ch == ';'):
                newLine += ch
    return newLine


def removeFunctionsAndConstructors(lines):
    balance = 0
    isFunction = False
    withoutFunctions = []
    for pos, line in enumerate(lines):
        line = line.strip(" ")
        if line.startswith("//") or len(line) <= 1:
            continue

        if line.startswith("template"):
            nxtLine = lines[pos + 1] if pos + 1 < len(lines) else ""
            if not nxtLine.startswith("struct"):
                continue

        openParentesis = line.count('(')
        closeParentesis = line.count(')')
        openBrackets = line.count('{')
        closeBrackets = line.count('}')

        balance += openBrackets - closeBrackets

        if isFunction:
            if balance == 1:
                isFunction = False
        elif balance + openBrackets > 1 and openParentesis > 0 and openParentesis == closeParentesis and openBrackets > 0:
            isFunction = True
        elif not isFunction:
            withoutFunctions.append(line)

        # print(line)
        # print(
        #     f"isFunction: {isFunction}, (x{openParentesis}, )x{closeParentesis}, {{x{openBrackets}, }}x{closeBrackets}, balance: {balance}")
        # print()

    return withoutFunctions


def write(data):
    debug.write(f"\n{data['template']}\n")
    debug.write(
        f"ostream& operator<<(ostream& os, const {data['name']}& tmp) {{ \n")
    for pos, field in enumerate(data['fields']):
        nxt = "" if pos + 1 == len(data['fields']) else "<< \", \""
        debug.write(f"  os << \"{field}: \" << tmp.{field} {nxt};\n")
    debug.write("  return os;\n}")


def extractStructs(pos, pref=""):
    if pos >= len(lines):
        return 1e9

    line = lines[pos].strip(" \n")

    if line.startswith("struct"):
        # loop until you extract all the content
        # Extract template <class A, ...> if any
        template = ""
        prevLine = lines[pos - 1].strip(" \n") if pos > 0 else ""
        if prevLine.startswith("template"):
            template = prevLine

        # Extract struct name
        name = line[6:-1] + template
        for trash in ["template", "class", "typename", " "]:
            name = name.replace(trash, "")

        heritagePos = name.find(":")
        if heritagePos != -1:
            name = name[:heritagePos]
        name = name.strip(" \n")

        if len(pref) > 0:
            name = pref + "::" + name

        structData = {
            'template': template,
            'name': name,
            'fields': []
        }

        pos += 1
        balance = 1
        while pos < len(lines):
            line = lines[pos].strip(" \n")
            balance += line.count('{')
            balance -= line.count('}')

            if balance == 0:
                break
            elif line.startswith("struct"):
                nxtPos = extractStructs(pos, structData['name'])
                # print("Children struct", line[6:], pos+1, "after", nxtPos+1, "balance", balance)
                pos = nxtPos
            else:
                line = removeDefaultValues(line)
                line = removePointers(line)
                fields = line.split()[1:]
                for field in fields:
                    structData['fields'].append(field)
                pos += 1

        write(structData)

    return pos


def findSomething(pieceOfCode):
    for pos, line in enumerate(lines):
        line = line.strip(" \n")
        if line.count(pieceOfCode) > 0:
            return pos
    return pos


def removeAddDebug():
    mainPos = findSomething("int main()")
    includeDebugH = findSomething("debug.h")
    includeDebugEtc = findSomething("debug(...)")

    file = open(filename, "w")

    for pos, line in enumerate(lines):
        if pos == includeDebugH or pos == includeDebugEtc:
            continue
        if pos == mainPos:
            file.write(
                "#ifdef LOCAL\n #include \"debug.h\"\n#else\n #define debug(...) 1 \n#endif\n")
        file.write(line)
    file.close()


# removeAddDebug()
lines = removeFunctionsAndConstructors(lines)

pos = 0
while pos < len(lines):
    pos = extractStructs(pos) + 1
