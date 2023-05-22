# Underperl

## Installation for Linux

1. Download gtk 3
2. Download / Clone the project repository
3. From the root of the directory:
   ```
   $ make
   ```

## Use the application

After installing the app, an executable named underperl while have been created at the root of project
To start the application from the terminal:

```
$ ./underperl
```

Our application allows you to determine if a word is accepted by a regex, detect text in a file, replace text in a file and replacing and detecting text in file simultaniously.

- ### Determine if a word is accepted by a regex

  You can check if a is part of a regex simply by inputing in the left input (regex) field the desired regex and by inputing in the right input field (word) the desired word. Upon pressing on execute, a message will be displayed on the right side of screen telling if the word is accepted by the regex or not.

- ### Detect text in a file

  First, select the file you desire to detect the text from using the file selector at the top left of the page. Toogle the detect button. Enter your regex in the corresponding field then press execute. The application will display on the left of the screen the lines where words accepted by the regex are located.

- ### Replace text in a file
  First, select the file you desire to detect the text from using the file selector at the top left of the page. Toogle the replace button. Enter your regex in the corresponding field, and enter the word you would like to replace the word accepted by the regex with, then press execute. The application will modify your file and it will also display it after the modifications on the right side of the screen

## Regex Syntax

- '+' : the or operator
- '.' or nothing : the and operator
- '\*' : Kleene Star
- [start - end] : exactly one of the characters form all characters in alphabetical order form the start character to the end character

## Contributors

- Amine Mike EL MAALOUF
- Attilio LEVIEILS
- Djibril TRAORE
