import hashlib
import os

'''
   Hashing is a one-way process that converts any data into a unique, irreversible value.
   Even a tiny change in input gives a completely different output — this is called the avalanche effect.

    hashlib is a built-in Python library used for hashing — turning data (like text, passwords, or files)
    into a fixed-length string of characters using algorithms such as SHA256, SHA1, or MD5.

    What You Can Use It For: 
     Password storage → store hashes instead of plain passwords
     File integrity checks → detect if a file was changed
     Digital signatures → verify authenticity of data
     Data comparison → check equality without revealing actual content

'''
## Testting to hash a Text 
'''
sample = "Hello Shayan"

hash_object = hashlib.sha256(sample.encode())

hash_digest = hash_object.hexdigest()


print(f"SHA of {sample} is {hash_digest}")

'''

def hash_file(file_path):

    file_path = os.path.expanduser(file_path)
  # New Hash Object!!
    h = hashlib.new("sha256")

    #Reading the file in bytes!
    with open(file_path,"rb") as file:
        while True:
            chunk = file.read(1024)
            if chunk == b"":
                break
            h.update(chunk)
        return h.hexdigest()


if __name__ == "__main__":
    ### Give the Path to the File to Hash!
    new = hash_file("something.txt")
    print(new)


