if __name__ == "__main__":
    # Read the original dashboard file
    dashboard_file = open("frontend.html", "r")
    contents = dashboard_file.read()
    dashboard_file.close()

    # Run the conversion
    contents = contents.replace("\n", "").replace("\t", "").replace("    ", "")

    output_file = open("local_variable.txt", "w+")
    output_file.write(contents)
    output_file.write("\n")
    output_file.write(str(len(contents)))
    output_file.close()