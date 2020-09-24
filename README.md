# Kaveri

## Project Structure

```bash
.
├── README.md
└── esb_app
    ├── Payload.json
    ├── bmd_files
    │   ├── 1600788368_1236854806
    │   │   └── bmd_8.xml
    │   ├── 1600788386_65243901
    │   │   └── bmd_T5.xml
    │   ├── 1600788402_1631457660
    │   │   └── bmd_T3.xml
    │   ├── 1600837869_1561508839
    │   │   └── bmd.xml
    │   ├── 1600837880_1438656102
    │   │   └── bmd_T1.xml
    │   ├── 1600837887_1462023884
    │   │   └── bmd_T2.xml
    │   ├── 1600837897_1635590950
    │   │   └── bmd_T3.xml
    │   ├── 1600837908_1521033520
    │   │   └── bmd_T4.xml
    │   ├── 1600837913_474941
    │   │   └── bmd_T5.xml
    │   ├── 1600837935_823021611
    │   │   └── bmd_6.xml
    │   ├── 1600837941_67982599
    │   │   └── bmd_7.xml
    │   ├── 1600837956_874988498
    │   │   └── bmd_8.xml
    │   ├── 1600838316_1989953645
    │   │   └── bmd_6.xml
    │   ├── 1600838330_948681673
    │   │   └── bmd_T1.xml
    │   ├── 1600838336_1261306334
    │   │   └── bmd_T2.xml
    │   ├── 1600838342_520765784
    │   │   └── bmd_T3.xml
    │   ├── 1600838347_72152185
    │   │   └── bmd_T4.xml
    │   ├── 1600838358_1024408692
    │   │   └── bmd_T5.xml
    │   ├── 1600838378_312806734
    │   │   └── bmd_7.xml
    │   └── 1600838384_1708537785
    │       └── bmd_8.xml
    ├── cert
    │   ├── key.pem
    │   └── server.pem
    ├── conf
    │   ├── build.conf
    │   └── esb_app.conf
    ├── dh2048.pem
    ├── esb.code-workspace
    ├── sql schema
    │   ├── esb_db.sql
    │   ├── routes.sql
    │   ├── transform_config.sql
    │   └── transport_config.sql
    └── src
        ├── BMD_Tests  -----> Contains files for unit testing
        │   ├── bmd.xml
        │   ├── bmd_6.xml
        │   ├── bmd_7.xml
        │   ├── bmd_8.xml
        │   ├── bmd_T1.xml
        │   ├── bmd_T2.xml
        │   ├── bmd_T3.xml
        │   ├── bmd_T4.xml
        │   └── bmd_T5.xml
        ├── adapter
        │   ├── email.c
        │   ├── email.h
        │   ├── http.c
        │   ├── http.h
        │   └── sftp.c
        ├── bmd ------------> modules relating to parsing of the bmd files.
        │   ├── Payload.json
        │   ├── bmd_parser.c
        │   ├── bmd_parser.h
        │   └── xmljson.c
        ├── db_access ------> modules of database access
        │   ├── change_status.c
        │   ├── database.c
        │   └── database.h
        ├── esb  --------> main logic of ESB
        │   ├── dynamiclookup.c
        │   ├── esb.c
        │   ├── esb.h
        │   ├── transform.c
        │   ├── transport.c
        │   └── worker.c
        ├── esb_app.c  -----> esb endpoint listening on port for incoming BMD
        ├── esb_rest.c  ---> Rest API provided bt the ESB
        └── test   -----> Unit Test Files
            ├── munit.c
            ├── munit.h
            ├── test_bmd_parser.c
            └── test_esb.c
```

## Essential Libraries to Install before using this Project
 Ensure that you have the essential libraries and headers , Run the following steps on the terminal
 ```bash
 Install required Libraries
 sudo apt update
 sudo apt install build-essential
 sudo apt install libssl-dev
 sudo apt install wget
 sudo apt install curl
 ```
1. Libxml2
    ```bash
    sudo apt-get install libxml2
    sudo apt-get install libxml2-dev
    ```

2. [MySql](https://dev.mysql.com/doc/mysql-apt-repo-quick-guide/en/).
3. Pthreads
4. Libcurl
5. [Kore Web Framework](https://docs.kore.io/4.0.0/install.html)


## Setting Up the MySQL Database For the Project

1. After installing MySQL get to the MySQL command line on the terminal.
```bash
Akshays-MacBook-Air:~ akshay$ mysql -u root -p
Enter password: 
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 8
Server version: 8.0.21 Homebrew

Copyright (c) 2000, 2020, Oracle and/or its affiliates. All rights reserved.

Oracle is a registered trademark of Oracle Corporation and/or its
affiliates. Other names may be trademarks of their respective
owners.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql> 
```
You should see a similar screen as above. You can replace root with your desired username.
The next step would be to run the SQL script to set up the database. The script can be found in the scripts directory inside esb_endpoint directory.
Run the following command to execute the script.
```bash
source Path/to/project/directory/esb_endpoint/scripts/SQLscript.sql;
```
This should create a database named esb_db with 4 tables.

2. Set up your Username and Password by changing corresponding fields in database.h file in src directory.

3. The tables in esb_db are as follows: 

i. esb_request table: (These are only some rows; The rows are added as you curl the bmd.xml)
    
```bash
    
mysql> select * from esb_request;
    
```
   
 ```bash   
+------+--------------------------------------+--------------------------------------+--------------+--------------------+--------------------------------------+---------------------+---------------+-----------+----------------+
| id   | sender_id                            | dest_id                              | message_type | reference_id       | message_id                           | received_on         | data_location | status    | status_details |
+------+--------------------------------------+--------------------------------------+--------------+--------------------+--------------------------------------+---------------------+---------------+-----------+----------------+
| 1045 | 556E2EAA-1D5B-5BC0-BCC4-4CEB669408DA | 6323D82F-4687-433D-AA23-1966330381FE | DebitReport  | INV-PROFILE-889712 | A3ECAEF2-104A-3452-9553-043B6D25386E | 2020-08-12 10:48:00 | NULL          | available | NULL           |
| 1179 | 522E2EAA-2D5B-8BC0-FCC4-5CEB669408DA | 5223D82F-4657-333D-BA23-2966330381FE | CreditReport | INV-PROFILE-889712 | D3ECAEF2-204A-3452-9553-043B6D25386E | 2020-08-12 10:48:00 | NULL          | available | NULL           |
| 1180 | 222E2EAA-1D5B-5BC0-BCC4-4CEB669408DA | 2223D82F-4687-433D-AA23-1966330381FE | CreditReport | INV-PROFILE-889712 | F3ECAEF2-204A-3452-9553-043B6D25386E | 2020-08-12 10:48:00 | NULL          | available | NULL           |
+------+--------------------------------------+--------------------------------------+--------------+--------------------+--------------------------------------+---------------------+---------------+-----------+----------------+
3 rows in set (0.00 sec)
```
ii. routes table: (You need to add rows here before hand so that there is valid {SENDER, DESTINATION, MESSAGE_TYPE} for esb_request table

```bash
mysql> select * from routes;
+----------+--------------------------------------+--------------------------------------+--------------+----------------------+
| route_id | sender                               | destination                          | message_type | is_active            |
+----------+--------------------------------------+--------------------------------------+--------------+----------------------+
|        1 | 756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA | 6393F82F-4687-433D-AA23-1966330381FE | CreditReport | 0x01                 |
|        2 | 556E2EAA-1D5B-5BC0-BCC4-4CEB669408DA | 6323D82F-4687-433D-AA23-1966330381FE | DebitReport  | 0x01                 |
|        3 | 666E2EAA-1D5B-5BC0-BCC4-4CEB669408DA | 8323D82F-4687-433D-AA23-1966330381FE | DebitReport  | 0x01                 |
|        4 | 222E2EAA-1D5B-5BC0-BCC4-4CEB669408DA | 2223D82F-4687-433D-AA23-1966330381FE | CreditReport | 0x01                 |
|       15 | 222E2EAA-1D5B-5BC0-BCC4-4CEB669408DA | 8323D82F-4687-433D-AA23-1966330381FE | CreditReport | 0x01                 |
|       16 | 522E2EAA-2D5B-8BC0-FCC4-5CEB669408DA | 5223D82F-4657-333D-BA23-2966330381FE | CreditReport | 0x01                 |
|       17 | 4ac26e80-f658-11ea-adc1-0242ac120002 | 4ac271fa-f658-11ea-adc1-0242ac120002 | CreditReport | 0x01                 |
|       18 | 5AC37984-B658-11EA-ADC1-0242AC120002 | BAC27A42-F658-11EA-adc1-0202AC120002 | DebitReport  | 0x01                 |
|       19 | 44428848-F658-11EA-ABC1-0242ABC20002 | 4AC22910-D658-11DA-ADC1-0242AC120002 | CreditReport | 0x01                 |
+----------+--------------------------------------+--------------------------------------+--------------+----------------------+
9 rows in set (0.00 sec)
```

iii. tranform_config: (These also need to be added with valid route_id that is present in routes table)

```bash
mysql> select * from transform_config;
+------+----------+----------------+--------------+
| id   | route_id | config_key     | config_value |
+------+----------+----------------+--------------+
| 1001 |        1 | Json_transform | json         |
| 1002 |        2 | Json_transform | json         |
| 1003 |        3 | Json_transform | json         |
| 1004 |        4 | Json_transform | json         |
| 1005 |       15 | Json_transform | json         |
| 1006 |       16 | Json_transform | json         |
| 1007 |       17 | Json_transform | json         |
| 1008 |       18 | Json_transform | json         |
| 1009 |       19 | Json_transform | json         |
+------+----------+----------------+--------------+
9 rows in set (0.00 sec)
```

iv. transport_config: (These also need to be added with valid route_id that is present in routes table)

```bash
mysql> select * from transport_config;
+------+----------+----------------------------+--------------+
| id   | route_id | config_key                 | config_value |
+------+----------+----------------------------+--------------+
| 2001 |        1 | https://ifsc.razorpay.com/ | HTTP         |
| 2002 |        2 | testkaveri123@gmail.com    | email        |
| 2003 |        3 | https://ifsc.razorpay.com/ | HTTP         |
| 2004 |        4 | https://ifsc.razorpay.com/ | HTTP         |
| 2005 |       15 | https://ifsc.razorpay.com/ | HTTP         |
| 2006 |       16 | testkaveri123@gmail.com    | email        |
| 2007 |       17 | https://ifsc.razorpay.com/ | HTTP         |
| 2008 |       18 | https://ifsc.razorpay.com/ | HTTP         |
| 2009 |       19 | Payload.json               | SFTP         |
+------+----------+----------------------------+--------------+
9 rows in set (0.00 sec)
```

## Build and Run the Project

1. Open the terminal in esb_app. (Eg: /home/user/Documents/Kaveri/kaveri-master/esb_app)
2. Build kodev
3. Run kodev
4. If there is no requests, open a new terminal window and run the following command:
  curl -k https://localhost:8888/bmd -F "bmd_file=@/your/working/directory/esb_endpoint/src/esb/Test_files/bmdT1.xml"
  (The processing will take few seconds, so if you want to add another request do the same as above again in new terminal window)
5. The bmd files are in Test_files
6. For email serivce you need to enter the file name exactly with extension that you want to send (eg: "Payload.json")
7. Also for sending email to your own account please refer to this: [less secure](https://devanswers.co/allow-less-secure-apps-access-gmail-account/)
8. For creating sftp connection please refer to this link: [sftp-ubuntu](https://linuxconfig.org/how-to-setup-sftp-server-on-ubuntu-20-04-focal-fossa-linux#:~:text=You%20can%20use%20your%20preferred,the%20window%20and%20click%20connect)
9. For status check using RESTful API use this command on new terminal window:
```bash
   curl -k  https://localhost:8888/rest?MessageID="enter messageID stored in esb_request table" --output -
```
10. If you face problem like bind(): Address already in use error when running kodev run. Run the following command: 
```bash
    fuser -k -n tcp 8888
```
