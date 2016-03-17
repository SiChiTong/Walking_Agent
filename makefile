# Specify the main target
TARGET = testAgent
# Default build type
TYPE = debug
TYPES =  debug release profile
BACKUP_DIR = .backup
SVN_INFO = svn_info
INSTALL_DIR = ..
# Which directories contain source files
SRC_DIRS = src src/sexpLibrary src/utils src/worldModel src/objects src/geometry src/skills src/etc  
DIRS = . ${SRC_DIRS} 

SETTINGS_FILES := .sshagent/*.rb
DIRS4BACKUP = . $(SRC_DIRS) ${TEST_DIRS} $(CONF_DIR)
# Which libraries are linked
LIBS = 
# Dynamic libraries
DLIBS = 

ifeq ($(TEST_ENABLED),true)
	LIBS = cppunit  dl
endif

# The next blocks change some variables depending on the build type
ifeq ($(TYPE),debug)
LDPARAM = 
CCPARAM = -Wall -g
MACROS =
endif

ifeq ($(TYPE),profile)
LDPARAM = -pg /lib/libc.so.5
CCPARAM = -Wall -pg
MACROS = NDEBUG
endif

ifeq ($(TYPE), release)
LDPARAM = -s
CCPARAM = -Wall -O2 
MACROS = NDEBUG
endif

# Add directories to the include and library paths
INCPATH = .
LIBPATH = 

# The compiler
C++ = g++

# Makes a list of the (.svn) folders.
SVN_ROOT_DIRS := $(foreach DIR,$(DIRS4BACKUP),$(wildcard $(DIR)/.svn))$
SVN_FILES := $(foreach DIR,$(DIRS4BACKUP),$(wildcard $(DIR)/.svn/**))$
SVN_DIRS := $(foreach SVN_DIR, $(SVN_ROOT_DIRS) $(SVN_FILES) ,$(wildcard $(SVN_DIR)/*))$
# Where to store object and dependancy files.
STORE = .make-$(TYPE)
# Makes a list of the source (.cpp) files.
SOURCE4BACKUP := $(foreach DIR,$(DIRS4BACKUP),$(wildcard $(DIR)/*.cpp))$ 
HEADER4BACKUP := $(foreach DIR,$(DIRS4BACKUP),$(wildcard $(DIR)/*.h))$
# Makes a list of the source (.cpp) files.
SOURCE := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.cpp))$
# List of header files.
HEADERS := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.h))
# Makes a list of the object files that will have to be created.
OBJECTS := $(addprefix $(STORE)/, $(SOURCE:.cpp=.o))
OBJECTS_DIR := 
#.libs/*.o
# Same for the .d (dependancy) files.
DFILES := $(addprefix $(STORE)/,$(SOURCE:.cpp=.d))

# Which files to add to backups, apart from the source code
EXTRA_FILES = makefile $(SVN_INFO) 

# Specify phony rules. These are rules that are not real files.
.PHONY: clean backup dirs

# Main target. The @ in front of a command prevents make from displaying
# it to the standard output.
$(TARGET): dirs $(OBJECTS)
	@echo Linking $(TARGET).
	@$(C++) -g -o $(TARGET) $(OBJECTS) $(OBJECTS_DIR) $(LDPARAM) $(foreach LIBRARY, \
	$(LIBS),-l$(LIBRARY)) $(foreach LIB,$(LIBPATH),-L$(LIB))

install: $(TARGET)
	@echo Copying install files to $(INSTALL_DIR)
	@-if [ ! -e $(INSTALL_DIR) ]; then mkdir $(INSTALL_DIR); fi;
	@-if [ ! -e $(INSTALL_DIR)/.sshagent ]; then mkdir $(INSTALL_DIR)/.sshagent; fi;
	@-if [ ! -e $(INSTALL_DIR)/log ]; then mkdir $(INSTALL_DIR)/log; fi;
	@cp -f $(TARGET) $(INSTALL_DIR)
	@cp -f $(SETTINGS_FILES) $(INSTALL_DIR)/.sshagent/
	
# Rule for creating object file and .d file, the sed magic is to add
# the object path at the start of the file because the files gcc
# outputs assume it will be in the same dir as the source file.
$(STORE)/%.o: %.cpp
	@echo Creating object file for $*...
	@$(C++) -Wp,-MMD,$(STORE)/$*.dd $(CCPARAM) $(foreach INC,$(INCPATH),-I$(INC))\
	        $(foreach MACRO,$(MACROS),-D$(MACRO)) -c $< -o $@
	@sed -e '1s/^\(.*\)$$/$(subst /,\/,$(dir $@))\1/' $(STORE)/$*.dd > $(STORE)/$*.d
	@rm -f $(STORE)/$*.dd

# Empty rule to prevent problems when a header is deleted.
%.h: ;

# Cleans up the objects, .d files and executables.
clean:
	@echo Making clean.
	@-rm -f $(foreach DIR,$(DIRS),$(STORE)/$(DIR)/*.d $(STORE)/$(DIR)/*.o)
	@-rm -f $(TARGET)

clean-all:
	@echo Making clean all.
	@-rm -f $(foreach TYP,$(TYPES),$(foreach DIR,$(DIRS),.make-$(TYP)/$(DIR)/*.d .make-$(TYP)/$(DIR)/*.o))
	@-rm -f $(foreach TARG,$(TARGETS),$(TARG))
# Backup the source files.
backup:
	@-if [ ! -e $(BACKUP_DIR) ]; then mkdir $(BACKUP_DIR); fi;
	@svn info > $(SVN_INFO)
	@tar -zcvf  $(BACKUP_DIR)/$(TARGET)_`date +%d%m%y_%H.%M`.tar.gz $(SOURCE4BACKUP) $(HEADER4BACKUP) $(CONF_FILES) $(EXTRA_FILES) $(SVN_DIRS) 
	@-if [ -e $(SVN_INFO) ]; then rm $(SVN_INFO); fi;
	@ echo Backup is finished and the file was copied in $(BACKUP_DIR).

# Create necessary directories
dirs:
	@-if [ ! -e $(STORE) ]; then mkdir $(STORE); fi;
	@-$(foreach DIR,$(DIRS), if [ ! -e $(STORE)/$(DIR) ]; \
	 then mkdir $(STORE)/$(DIR); fi; )

# Includes the .d files so it knows the exact dependencies for every
# source.
-include $(DFILES)
