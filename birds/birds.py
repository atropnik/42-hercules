# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    birds.py                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atropnik <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 16:37:18 by atropnik          #+#    #+#              #
#    Updated: 2019/04/05 17:39:38 by atropnik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import sys

class bc:
    HEADER = '\033[95m'
    OKPROJECT = '\033[94m'
    PRINTOK = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    CLOSING = '\033[0m'
    UNDERLINE = '\033[4m'
    BOLD = '\033[1m'

if not len(sys.argv) > 2:
	print bc.FAIL + " ----> usage: python birds.py <directory name> <project language> <----"  + bc.CLOSING
	sys.exit()

MY_HOME = os.environ['HOME']
ME = os.environ['LOGNAME']
NVM = 'https://raw.githubusercontent.com/creationix/nvm/v0.33.1/install.sh' #this loads Node Version Manager
NAME = sys.argv[1]
LANG = sys.argv[2]
path = MY_HOME + '/' + NAME

def gen_gitignore( LANG, NAME ):
	gitignore = open(path + '/.gitignore', 'wr+')
	gitignore.write('# System Files\n*.DS*\n*.swp*\n*._*\n*.dll\n\n')
	if (LANG == 'C' or LANG == 'c'):
		gitignore.write('# C\n*.o\n\n# Executables\n*.exe\n*.out\n\n# Debug Files\n*.dSYM/\n\n')
	print bc.PRINTOK + ' (x) .gitignore added.\n' + bc.CLOSING
	gitignore.close()

def gen_makefile( NAME ):
	file = open(path + '/Makefile','wr+')
	file.write('# MAKEFILE : ' + NAME + '\n\n' + 'NAME = ' + NAME + '\n\n' + 'SRC += main.c' + '\n\n' + 'OBJ = $(SRC:.c=.o)')
	make_lft = ""
	flag_lft = ""
	libft = 'libft'
	if (raw_input(' -> Copy libft from home directory into project root (y/n)? ') == 'y'):
		if os.path.exists(MY_HOME + '/' + libft):
			if not os.path.exists(path + '/libft'):
				os.system('mkdir ' + path + '/libft')
			os.system('cp -a ' + MY_HOME + '/' + libft + '/. ' + path + '/libft/')
		else:
			print bc.FAIL + " (Error) no libft/ directory found in " + MY_HOME + bc.CLOSING
		make_lft = "\tmake -C libft/\n"
		flag_lft = " -L libft -lft"
		print bc.PRINTOK + " (x) libft/ added to project.\n" + bc.CLOSING
	name_rules = "$(NAME): $(OBJ)\n" + make_lft + "\t$(CC) $(OBJ) -o $(NAME)" + flag_lft + '\n\n'
	file.write('\n\n' + 'CC = gcc -Wall -Wextra -Werror\n\n')
	file.write(name_rules + 'all: $(NAME)\n\nclean:\n\t@rm -rf $(OBJ)\n\nfclean: clean\n\t@rm -rf $(NAME) $(OBJ) \n\nre: fclean $(NAME)')
	print bc.PRINTOK + ' (x) Makefile added to create executable ./' + NAME + '\n' + bc.CLOSING
	file.close()

def gen_header( NAME ):
	header = open(path + '/' + NAME + '.h','wr+')
	header.write('#ifndef ' + NAME.upper() + '_H\n# define ' + NAME.upper() + '_H\n\n# include <libraries>\n\n#endif')
	print bc.PRINTOK + ' (x) ' + NAME + '.h created.\n' + bc.CLOSING
	header.close()

def gen_author( NAME ):
        author = open(path + '/' + 'author','wr+')
	author.write(ME + '\n')
        print bc.PRINTOK + ' (x) author file with author \'' + ME + '\' created.\n' + bc.CLOSING
	author.close()

def generate_files (LANG, NAME):
	if (LANG == 'C' or LANG == 'c'):
		gen_makefile(NAME)
		gen_header(NAME)
	else:
		if LANG == 'node' and not os.path.exists(MY_HOME + '/.nvm') and not os.path.exists(MY_HOME + '/.npm'):
			if (raw_input(' Previous node install not found. Run nvm installation script from source (y/n)? ') == 'y'):
				os.system('curl -o- ' + NVM + '| bash')
				print bc.PRINTOK + ' (x) node installed.\n' + bc.CLOSING
		else:
			print bc.PRINTOK + ' (x) verified global node installation.\n' + bc.CLOSING
	gen_gitignore(LANG, NAME)
	if (raw_input(' -> Create author file (y/n)? ') == 'y'):
		gen_author(NAME)

if not os.path.exists(path):
	os.makedirs(path)
	print bc.PRINTOK + '\n (x) created directory ' + path + '\n' + bc.CLOSING
else:
	print bc.PRINTOK + ' (x) verified directory ' + path + ' already exists.\n' + bc.CLOSING
generate_files(LANG, NAME)

print bc.OKPROJECT + '\n -------- Project initiated successfully. -------- \n' + bc.CLOSING
