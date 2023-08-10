import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

# Email settings
smtp_server = 'smtp-mail.outlook.com'
smtp_port = 587
email_address = 'your_email@example.com'
email_password = 'your_app_password'
recipient = 'recipient@example.com'

# Create the email
subject = 'Raspberry Pi Notification'
message = 'Hello, this is a test email from Raspberry Pi!'
msg = MIMEMultipart()
msg['From'] = email_address
msg['To'] = recipient
msg['Subject'] = subject
msg.attach(MIMEText(message, 'plain'))

# Connect to SMTP server and send email
try:
    server = smtplib.SMTP(smtp_server, smtp_port)
    server.starttls()
    server.login(email_address, email_password)
    server.sendmail(email_address, recipient, msg.as_string())
    server.quit()
    print("Email sent successfully!")
except Exception as e:
    print("An error occurred:", str(e))
