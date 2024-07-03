# hyprland-keybind-viewer

[![MIT](https://img.shields.io/github/license/BlacklightYT/python-discord-bot?color=a3425d)](https://github.com/BlacklightYT/python-discord-bot/blob/main/LICENSE) ![Static Badge](https://img.shields.io/badge/Programming_Language-black?style=flat&logo=C)

> [!IMPORTANT]
> Everything in this program is text-based
> 
> and no rendering library like qt or gtk ... is used
> 
> Using any font like monospace won't do,
>
> since every character has it's own spacing

## Prolog?

Upfront I wanted to let you know. I am an Informatics Student at the Friedrich-Alexander University in Erlangen, Germany. I am only in my second Semester, thus you might encounter bugs (I wanted a working program first before actually handling Errors). The MIT License Rules apply and therefore I cannot be held accountable for any problems you encounter but you shall not refrain from contacting me on such a case :D 

The program standards I use (that get used in my uni):`-std=c11 -pedantic -Wall -Werror -D_XOPEN_SOURCE=700`

This program should be memory leak proof according to valgrind (valgrind.txt)

# Functionality

Now to the Program itself:
We could describe this as a pipeline of multiple objectives. Firstly we want to extract the the keybinds of your config file and transform them into a format to simplify the rendering process [keys.sh]. The Rendered Product gets written into a text file. At last, we open the text file with anything we want to display it with. In my case, I use the kitty terminal with a read-only vim session. Adding a bind to open/close the window (Also adding a rule to hyprland to make it floating).

## In short: 
> Extract Keybinds -> main.c -> keybinds.txt
>
> keybinds.sh (keybinds.txt) -> hyprland.conf 

# Compiling
```  
gcc -std=c11 -pedantic -Wall -Werror -D_XOPEN_SOURCE=700 -o generate_file keybind_file_generator.c
```
# Usage

Modify the shell script to your heart's content. (Using ChatGPT simplifies this process. I used it with the addition of another person's shell script [source](https://github.com/jason9075/rofi-hyprland-keybinds-cheatsheet))
The format in the end should be something like: `key key [...], action, command` The should be a big limit on how many keys you want to add. In my terms `key` is something like `ctrl` while `action` is any key that isn't special like `y`.

```
generate_file > keybinds.txt
```
And done!
