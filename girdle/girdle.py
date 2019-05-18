import getpass
import smtplib
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText

 

fromaddr = raw_input('what is your email address (enter STD if it is your standard on this machine): ')
passwd = getpass.getpass('your email password : ')
toaddr = raw_input('recipient\'s address (or 42 USA user ID): ')
serveraddr = raw_input('smtp server address (enter GM to use smpt.gmail.com): ')

if fromaddr == 'STD':
	fromaddr = 'atropnikova@gmail.com'
if '@' not in toaddr:
	toaddr = toaddr + '@student.42.us.org'
if serveraddr == 'GM':
	serveraddr = 'smtp.gmail.com'

subj = raw_input('email subject (enter STD if you are Hercules needing army): ')
bodyemail = raw_input('message body (enter STD if you are fighting Amazons rn): ')

if subj == 'STD':
	subj = 'calling all warrior dudes and dudettes!'
if bodyemail == 'STD':
	bodyemail = 'Come help me fight Amazons. It will be GoodTymeTM. Armor and food rations not included.\n \n Love,\n Hercules.\n'


msg = MIMEMultipart()
msg['From'] = fromaddr
msg['To'] = toaddr
msg['Subject'] = subj
 
body = bodyemail
msg.attach(MIMEText(body, 'plain'))
 
server = smtplib.SMTP('smtp.gmail.com:587')
server.ehlo()
server.starttls()
server.login(fromaddr, passwd)
text = msg.as_string()
server.sendmail(fromaddr, toaddr, text)
print "\nCall to arms has been sent."
server.quit()
