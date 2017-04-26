"""
Generate test data of irreducible polynomial over GF(p).
"""
import os
import re


# parameters
num_test_data = 10
current_dir = os.path.dirname(__file__)
input_filepath = os.path.join(current_dir, "irreducible_polynomial.txt")
output_filepath = os.path.join(current_dir, "../irreducible_polynomial.txt")


def to_str(coeffs):
    """gen_test_data

    :param coeffs: If X^{1}, coeffs is "10".
    """
    # reverse string order
    coeffs = coeffs[::-1]
    content = ", ".join(['{0}'.format(c) for c in coeffs])
    return "{{{0}}},\n".format(content)


def main():
    output = []

    num_irreducible_polynomial = 1
    # read irreducible polynomial from files
    with open(input_filepath, "r") as f:
        for line in f.readlines():
            # remove lines starting with #
            if re.match(r"^[^#]", line) is not None:
                num, coeffs = line.rstrip().split(" ")
                output.append(to_str(coeffs))
                num_irreducible_polynomial += 1
            # if number of test data is read
            if num_irreducible_polynomial >= num_test_data:
                break

    # output c++ style irreducible polynomial
    with open(output_filepath, "w") as f:
        f.writelines(output)


if __name__ == '__main__':
    main()
