#!python
import sys

# Create the environment and create a Compilation Database for use in VSCodium
env = DefaultEnvironment(tools=['default', 'compilation_db'])

if sys.platform.startswith('linux'):
    env.Append(CXXFLAGS = '-std=c++11 -O3')
    program_ending = '.out'
elif sys.platform == 'darwin':
    env.Append(CXXFLAGS = '-std=c++11 -O3')
    program_ending = '.out'
elif sys.platform == 'win32' or sys.platform == 'msys':
    env.Append(CCFLAGS=['/EHsc', '/O2'])
    program_ending = '.exe'
else:
    host_platform = "Unknown platform: " + sys.platform
    exit(1)

    
env.CompilationDatabase()

target_name = 'algocomparision' + program_ending

Program(target_name, Glob('*.cpp'))
