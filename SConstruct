#!python

# Create the environment and create a Compilation Database for use in VSCodium
env = DefaultEnvironment(tools=['default', 'compilation_db'])
env.CompilationDatabase()

Program('program.out', Glob('*.cpp'))
