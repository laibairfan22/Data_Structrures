# Data_Structrures
A Text Editor using trie tree and huffman coding

Welcome to Smart Text Editor, a console-based text editor developed in C++. This text editor provides users with the ability to type, edit, and save text, along with smart word completion and text compression features.

# Project Overview
## Purpose
The purpose of this project is to develop a user-friendly and efficient text editor with advanced features such as smart word completion and text compression.

## Features
### Typing Text:

- Users can type text in a console-based environment.
- Forward typing only; no backward editing allowed.
  
### Word Completion Suggestions:

- Trie trees or B-trees are used for suggesting word completions.
- Users receive suggestions as they type, enhancing typing efficiency.
  
### Compression of Text:

- Utilizes Huffman encoding for text compression.
- Compressed text and compression tree are saved for later retrieval.

### Saving and Loading:

- Users can save compressed text and compression tree to a local .txt file.
- Text can be loaded from a pre-saved file.
  
### Uncompressing of Text:

Huffman compression tree is used to decompress the text and recover the original content.

### Continue Editing:

- Users can resume typing from where they left off.
- Multiple save and load cycles are supported.
  
## Implementation Guidelines
- Typing Text
- Implemented using vector strings, iterators, and loops.
- Only forward typing is allowed; no backward editing.
- Word Completion Suggestions
- Trie trees or B-trees used for suggesting word completions.
- Trie-tree constructed over the provided dictionary.
- Compression of Text
- Huffman encoding employed for text compression.
- Compressed text and compression tree stored for later use.
- Saving and Loading
- Compressed text and compression tree saved to a local .txt file.
- Simple file handling used for reading and writing.
- Uncompressing of Text
- Huffman compression tree loaded to decompress the compressed text.
- Continue Editing
- Users can continue editing from the recovered text.
- Supports multiple save and load cycles.
  
## How to Use
- Clone the repository.
- Compile and run the Smart Text Editor program.
- Follow the on-screen instructions for typing, saving, loading, and editing text.

# SnapShots
## Landing Page

![image](https://github.com/laibairfan22/Data_Structrures/assets/139337014/8f5119e4-0e13-438c-8c30-17367788767d)

## Rules

![image](https://github.com/laibairfan22/Data_Structrures/assets/139337014/a416f67e-0748-4167-9129-9659fa9e641d)


## Options

![image](https://github.com/laibairfan22/Data_Structrures/assets/139337014/92d390db-acf1-415d-b085-9ea9c8e10c54)




