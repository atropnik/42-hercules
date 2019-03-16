# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    keys.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atropnik <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/15 21:44:28 by atropnik          #+#    #+#              #
#    Updated: 2019/03/15 21:45:46 by atropnik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cp ~/.zshrc ~/.zshrc_backup

echo "export FINDER42_UID=224763d2e1f209f1b7e7185dc6948cf4c0261df5a854697bcbb2c5dcf89fc601" \
>> ~/.zshrc
echo "export FINDER42_SECRET=23ced8ff4ac4db03d9899bf3adfa6e742b5a40dcd8c70a75a5deacfcaf015aaa" \
>> ~/.zshrc

zsh
