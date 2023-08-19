from pyfingerprint.pyfingerprint import PyFingerprint

# Initialize the fingerprint sensor
try:
    f = PyFingerprint('/dev/ttyS0', 57600, 0xFFFFFFFF, 0x00000000)
# 57600: the second argument passed to the constructor specifies the baud rate for serial communication 
# 0xFFFFFFFF: the third argument passed to the constructor represents the default password of the fingerprint sensor. 
# 0x00000000: the fourth argument passed to the constructor represents the default address of the fingerprint database within the sensor's memory.   
    if not f.verifyPassword():
        raise ValueError('The given fingerprint sensor password is wrong!')

except Exception as e:
    print('Error: ', e)
    exit(1)

print('Currently used templates: {0}/{1}'.format(f.getTemplateCount(), f.getStorageCapacity()))
# Prompt the user to choose an action
print("Choose an action:")
print("1. Save a fingerprint")
print("2. Search for a fingerprint")
choice = input("Enter your choice (1/2): ")

if choice == '1':
    # Save a fingerprint
    try:
        print('Waiting for finger...')

        while not f.readImage():
            pass

        f.convertImage(0x01)
        position = f.storeTemplate()

        if position != -1:
            print('Fingerprint stored at position #{}'.format(position))
        else:
            print('Failed to store fingerprint')

    except Exception as e:
        print('Error: ', e)
        exit(1)

elif choice == '2':
    # Search for a fingerprint
    try:
        print('Waiting for finger...')

        while not f.readImage():
            pass

        f.convertImage(0x01)

        result = f.searchTemplate()

        if result[0] >= 0:
            position = result[0]
            accuracy = result[1]
            print('Fingerprint found at position #{} with accuracy {}'.format(position, accuracy))
        else:
            print('Fingerprint not found')

    except Exception as e:
        print('Error: ', e)
        exit(1)

else:
    print("Invalid choice")
