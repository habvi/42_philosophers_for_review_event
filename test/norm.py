import subprocess
import sys

# ----------------------------------------------------------
# 1. Your setting
# All directories & files -> NORM_CHECK_PATH = ""
# Select paths            -> NORM_CHECK_PATH = "dir_name file_path ..."

NORM_CHECK_PATH = "../philo/includes ../philo/srcs"

# 2. Your setting
# Nothing is ignored      -> IGNORE_WARNING = []
# Select ignored warnings -> IGNORE_WARNING = [ignore_warning1, ignore_warning2, ...]
LINE_HEADER = "INVALID_HEADER"
LINE_COMMENT = "WRONG_SCOPE_COMMENT"
LINE_EMPTY = "EMPTY_LINE_FUNCTION"

IGNORE_WARNING = [LINE_HEADER,
                LINE_COMMENT,
                LINE_EMPTY]

# ----------------------------------------------------------
LOG_FILE = "../test/norm.log"
LINE_OK = "OK!"
LINE_ERR = "Error!"

# ----------------------------------------------------------
# color
WHITE = "white"
RED = "red"
GREEN = "green"
COLOR_DICT = {"white" : "\033[37m",
              "red" : "\033[31m",
              "green" : "\033[32m",
              "end" : "\033[0m"}

def print_color_str(color=WHITE, text=""):
    print(COLOR_DICT[color] + text + COLOR_DICT["end"])

def print_color_str_no_lf(color=WHITE, text=""):
    print(COLOR_DICT[color] + text + COLOR_DICT["end"], end="")

# ----------------------------------------------------------
# put
def debug_lines(lines):
    for line in lines:
        print(line, end="")
    print("-----------------------")

def put_result(passed):
    if passed:
        print_color_str(GREEN, "[OK]")
        exit(0)
    else:
        print_color_str(RED, "[NG]")
        exit(1)

# ----------------------------------------------------------
# run
def run_command(command):
    subprocess.run(command, shell=True)

# ----------------------------------------------------------
def check_each_file(lines):
    if len(lines) >= 2:
        debug_lines(lines)
        return False
    return True

def is_selected_ignore_line(line):
    for ignore_line in IGNORE_WARNING:
        if ignore_line in line:
            return True
    return False

def custom_norm_check():
    passed = True
    with open(LOG_FILE) as f:
        try:
            lines = []
            for line in f:
                if LINE_ERR in line:
                    passed &= check_each_file(lines)
                    lines = [line]
                else:
                    if LINE_OK in line:
                        continue
                    if is_selected_ignore_line(line):
                        continue
                    lines.append(line)
            passed &= check_each_file(lines)
            return passed
        except FileNotFoundError as err:
            print(err)
            exit(1)

def set_norm_check_paths():
    argc = len(sys.argv)
    if argc == 1:
        return NORM_CHECK_PATH
    return " ".join(sys.argv[1:])

def run_norm(norm_check_paths):
    command = "python3 -m norminette " + norm_check_paths +  " > " + LOG_FILE
    print(command)
    run_command(command)
    return custom_norm_check()

def main():
    norm_check_paths = set_norm_check_paths()
    passed = run_norm(norm_check_paths)
    put_result(passed)

if __name__ == '__main__':
    main()