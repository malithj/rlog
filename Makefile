########################################################################## 
# rlog Example Project                                                   #
# Copyright (c) 2020 Malith Jayaweera https://malithjayaweera.com        #
#                                                                        #
# This program is free software: you can redistribute it and/or modify   #
# it under the terms of the GNU General Public License as published by   #
# the Free Software Foundation, either version 3 of the License, or      #
# (at your option) any later version.                                    #
#                                                                        #
# This program is distributed in the hope that it will be useful,        #
# but WITHOUT ANY WARRANTY; without even the implied warranty of         #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          #
# GNU General Public License for more details.                           #
#                                                                        #
# You should have received a copy of the GNU General Public License      #
# along with this program.  If not, see <https://www.gnu.org/licenses/>. #
##########################################################################

CC=g++
CFLAGS=-std=c++11
TARGET=main
BUILD_DIR=build
MKDIR_P=mkdir -p
OUT_DIR=$(BUILD_DIR)
INCLUDE_DIR=include

all: $(OUT_DIR) $(TARGET) 

%.o : %.cc
	@echo "Building object file: $@"	
	$(CC) -o $(OUT_DIR)/$@ -c $^ $(CFLAGS)
	@echo ""

$(OUT_DIR):
	@echo "Creating directory: $(OUR_DIR)" 
	${MKDIR_P} ${OUT_DIR}
	@echo ""

main: main.o
	@echo "Linking object file $@ with $^"
	$(CC) -o $(OUT_DIR)/$@ $(OUT_DIR)/$^ $(CFLAGS) -I $(INCLUDE_DIR)
	@echo ""

.PHONY: clean

clean:
	rm -rf $(OUT_DIR)/*.o $(OUT_DIR)/main
