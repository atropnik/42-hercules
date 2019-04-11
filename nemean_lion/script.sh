# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    script.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atropnik <atropnik@42.us.org>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/01 22:27:01 by atropnik          #+#    #+#              #
#    Updated: 2019/03/01 22:38:51 by atropnik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# run as root

apt-get install openssh-server -y

PORT_NUMBER="42"

sed -i "s/^Port .*/Port $PORT_NUMBER/g" /etc/ssh/sshd_config

service ssh restart
