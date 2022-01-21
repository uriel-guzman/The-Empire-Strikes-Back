**Files**

The following files determine the order of the topics/chapters in the book.

- ```allCodes.txt```:

  Contains all topics inside ```Codes/...```

  The order inside, will be the final order of the book

  Use ```~Topic``` to don't display it in the book 
    - DSU rollback (first topic)
    - ~DSU (not displayed)
    - ~Foldable deque (not displayed)
    - Monotone queue (second topic)

- ```chaptersOrder.txt```:
Contains all chapters, in the order we want to display them in the book 
To create a new chapter just gather all files in the same folder

**Extra** 

If the complexity of the algorithm is needed, add a ```.tex``` file with the same name as the ```.cpp```

 - ```Mos.cpp``` (algorithm)
 - ```Mos.tex``` (LaTeX extra information)

For the ```.tex``` file add in the **first** line the complexity, the other lines could be used to add more information about the algorithm.


**Generate the book**

Simply run ```python3 createBook.py```


