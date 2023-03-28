import csv

def evaluate_mean(filename):
    with open(filename) as reference_file:
        reference_reader = csv.reader(reference_file)
        length = 0
        sum = [0, 0, 0]

        for red, green, blue in reference_reader:
            if red != "Red":
                length += 1
                sum[0] += int(red)
                sum[1] += int(green)
                sum[2] += int(blue)

        print(f"Mean values for file {filename}")
        sum[0] = sum[0] / length
        print(f"Red mean: {str(sum[0])}")
        sum[1] = sum[1] / length
        print(f"Green mean: {str(sum[1])}")
        sum[2] = sum[2] / length
        print(f"Blue mean: {str(sum[2])}")
        print()

if __name__ == "__main__":
    evaluate_mean("measurements_white.csv")
    evaluate_mean("measurements_black.csv")