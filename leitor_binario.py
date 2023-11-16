import struct

def read_binary_file(file_path):
    data = []

    with open(file_path, 'rb') as file:
        while True:
            # Read the binary data for one record
            record_data = file.read(struct.calcsize('Qf'))

            # Check if we have reached the end of the file
            if not record_data:
                break

            # Unpack the binary data using struct.unpack
            position, frequency = struct.unpack('Qf', record_data)

            # Store the data as a tuple
            data.append((position, frequency))

            # Print the data for this iteration
            print(f"Read: Position={position}, Frequency={frequency}")

    return data

# Example usage
file_path = './novoTeste/vet/teste3.bin'
result = read_binary_file(file_path)

# Print the result
for position, frequency in result:
    print(f"Final Result: Position={position}, Frequency={frequency}")
