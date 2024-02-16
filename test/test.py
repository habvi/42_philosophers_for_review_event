import subprocess

EXEC_FILE_PATH = "../philo/philo"

# ----------------------------------------------------------
# color
WHITE = "white"
RED = "red"
GREEN = "green"
END = "end"
COLOR_DICT = {"white" : "\033[37m",
              "red" : "\033[31m",
              "green" : "\033[32m",
              "end" : "\033[0m"}

def print_color_str(color=WHITE, text=""):
    print(COLOR_DICT[color] + text + COLOR_DICT[END])

def print_color_str_no_lf(color=WHITE, text=""):
    print(COLOR_DICT[color] + text + COLOR_DICT[END], end="")


# ----------------------------------------------------------
def run(test_name, args, expected_returncode):
    print("----- " + test_name + " -----")

    command = [EXEC_FILE_PATH] + args
    print(*command)
 
    proc = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = proc.communicate(command, timeout=2)

    print("status code: ", proc.returncode)
    print("stdout: ", stdout)
    print("stderr: ", stderr)

    if proc.returncode == expected_returncode:
        print_color_str(GREEN, "[OK]")
        return 0
    else:
        print(RED, "[NG]")
        return 1


def run_normal_case():
    test_result = 0

    test_result |= run("Test1", ["4", "410", "200", "200", "2"], 0)

    return test_result


def run_error_case():
    test_result = 0

    # not 5 or 6 arguments
    test_result |= run("Test1", ["0", "1", "2"], 1)
    # not 5 or 6 arguments & 0 philo
    test_result |= run("Test2", ["0", "1", "2", "3"], 1)
    # correct 5 arguments & 0 philo
    test_result |= run("Test3", ["0", "1", "2", "3", "4"], 1)
    # correct 6 arguments & 0 philo
    test_result |= run("Test4", ["0", "1", "2", "3", "4", "5"], 1)

    return test_result


def main():
    test_result = 0

    # test_result |= run_normal_case()
    test_result |= run_error_case()

    exit(test_result)


if __name__ == '__main__':
    main()
