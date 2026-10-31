# NvmStorage

Wrapper class for storing a serializable object in NVM.

[NvmStorage](nvmStorage.hpp): NvmStorage class definition

[NvmStorageExample](nvmStorageExample.hpp): Example class using NvmStorage

## Suggested usage

**Task definition**:

    #include "nvmStorageExample.hpp"  // Change to actual location of the storage class

    ...

    private:
        NvmStorageExample m_NvmStorageExample{"nvmStorage"};
        std::string m_StorageRoot;

**initialize()**:

    // Load from Nvm
    m_NvmStorageExample.initialize(getTaskParse());

**executive()**:

    // Store values
    m_NvmStorageExample.setExample1(42);

**cleanup()**:

    // Force a write to Nvm
    m_NvmStorageExample.save();
