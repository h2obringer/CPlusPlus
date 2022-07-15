drop table books cascade constraints;
create table books (
  isbn varchar2(15),
  author varchar2(100) not null,
  title varchar2(128) not null,
  price number(7,2) not null,
  subject varchar2(30) not null,
  primary key (isbn)
);

insert into books values ('0439139597', 'J. K. Rowling', 
'Harry Potter and the Goblet of Fire', 25.95, 'CHILDREN');
insert into books values ('0439064864', 'J. K. Rowling', 
'Harry Potter and the Chambers of Secrets', 17.95, 'CHILDREN');
insert into books values ('0439136350', 'J. K. Rowling', 
'Harry Potter and the chamber of secrets', 19.95, 'CHILDREN');
insert into books values ('0345350499', 'Marion Zimmer Bradley', 
'The mists of avalon', 12.95, 'FICTION');
insert into books values ('0395851580', 'James Marshall', 
'George and Martha: Complete stories of two best friends', 25.00, 'CHILDREN');
insert into books values ('0375810609', 'Jean DE Brunhoff', 
'Bonjour Babar', 29.95, 'CHILDREN');
insert into books values ('0345337662', 'Anne Rice', 
'Interview with a vampire', 6.99, 'FICTION');
insert into books values ('0345377648', 'Anne Rice', 
'Lasher', 14.00, 'FICTION');
insert into books values ('0345313860', 'Anne Rice', 
'The vampire lestat', 6.99, 'FICTION');
insert into books values ('034538475x', 'Anne Rice', 
'The tale of the body thief', 6.99, 'FICTION');
insert into books values ('0201612585', 'Rajshekhar Sunderraman', 
'Oracle8 Programming a primer', 29.99, 'COMPUTERS');
insert into books values ('0910146691', 'Allen DE Hart', 
'North Carolina Hiking Trails', 14.95, 'NONFICTION');
insert into books values ('0887251714', 'Jim Cottrell', 
'Skiing Everyone', 10.00, 'NONFICTION');
insert into books values ('0030615372', 'Colin M. Turnbull', 
'The Mbuti Pygmies', 15.00, 'NONFICTION');
insert into books values ('0201634422', 'S Keshav', 
'An Engineering Approach to computer networks', 49.95, 'NONFICTION');
--
insert into books values ('1861004060','Paul Wilton',
'Beginning Javascript',31.99,'COMPUTERS');
insert into books values ('0130893404','Marty Hall',
'Core Servlets and JavaServer Pages (JSP)', 34.39,'COMPUTERS');
insert into books values ('1565926919','Steve Muench',
'Building Oracle XML Applications', 35.96,'COMPUTERS');
insert into books values ('1572316950','Jeff Prosise',
'Programming Windows With MFC', 47.99,'COMPUTERS');
insert into books values ('0130281875','Bob Toxen',
'Real World Linux Security',35.99,'COMPUTERS');
insert into books values ('0521794897','W. T. Tutte',
'Graph Theory',31.95,'MATHEMATICS');
insert into books values ('0471317160','Gerald B. Folland',
'Real Analysis',84.95,'MATHEMATICS');
insert into books values ('0881336653','Dan Saracino',
'Abstract Algebra: A First Course', 37.95,'MATHEMATICS');
insert into books values ('0471170550','Howard Anton',
'Elementary Linear Algebra', 148.75,'MATHEMATICS');
insert into books values ('1558606793','Didier H. Besset',
'O-O Implementation of Numerical Methods',54.95,'MATHEMATICS');
insert into books values ('0802713521','David Bodanis',
'E=mc2: A Biography of the World''s Most Famous Equation',20.00,'PHYSICS');
insert into books values ('0810943646','Curt Suplee et al',
'PHYSICS in the 20th Century',24.99,'PHYSICS');
insert into books values ('0195120426','Clifford A. Pickover',
'Time: A Traveler''s Guide', 20.00,'PHYSICS');
insert into books values ('0231120788','Sten F. Odenwald',
'The 23rd Cycle: Learning to Live With a Stormy Star',22.36,'PHYSICS');
insert into books values ('1575001578','Gregory Benford',
'Beyond Human: The New World of Cyborgs and Androids' ,22.05,'PHYSICS');

--NAME: Xiukun Chang
insert into books values('0865420769','Norman H. Sleep','Principles of Geophysics',43.00,'GEOPHYSICS');
insert into books values('0387963871','Joseph Pedlosky','Geophysical Fluid Dynamics',38.00,'GEOPHYSICS');
insert into books values('0195108086','Rick Salmon','Lectures on Geophysical Fluid Dynamics',27.95,'GEOPHYSICS');
insert into books values('0471819565','Frank D.Stacey','Physics of the Earth',69.95,'GEOPHYSICS');
insert into books values('0124340709','John Smith','Small Scale Processes in Geophysical Fluid Flows',42.95,'GEOPHYSICS');
insert into books values('0895737272','Paul G.Mezey','Shape in Chemistry',20.00,'CHEMISTRY');
insert into books values('0306335034','Henry F.Schaefer','Modern Theoretical Chemistry',56.95,'CHEMISTRY');
insert into books values('3540586725','J.D.Dunitz','Topics in Current Chemistry',29.95,'CHEMISTRY');
insert into books values('0470210109','Z.B.Maksic','Modelling of Structure and Properties of Molecules',78.00,'CHEMISTRY');
insert into books values('0471995770','John N.Murrell','The Chemical Bond',32.00,'CHEMISTRY');
insert into books values('0521391849','Lee A.Segel','Biological Kinetics',17.95,'BIOLOGY');
insert into books values('0471577359','Frederick M.Ausubel','Short Protocols in Molecular',19.95,'BIOLOGY');
insert into books values('0854044728','Ginny C. Saunders','Analytical Molecular',28.00,'BIOLOGY'); 
insert into books values('3110141132','Steffen Schdze Kremer','Molecular Bioinformatics',40.00,'BIOLOGY'); 
insert into books values('0070608989','Valliam D.Stansfield','Molecular and Cell Biology',14.95,'BIOLOGY'); 

--NAME: Wei Chen
insert into books VALUES ('0534368018', 'Bronson, Gary J.', 'A First Book of C++: From Here to There', 60.95, 'C++ Programming');
insert into books VALUES ('1584500492', 'DeLoura, Mark', 'Game Programming Gems', 69.95, 'Game Programming');
insert into books VALUES ('076454621X', 'Murdock, Kelly L.', '3D Studio Max R3', 49.99,   'Computer Graphics');
insert into books VALUES ('0136603904', 'Irvine, Kip R.', 'Assembly Language for Intel-  Based Computers', 72.95, 'Assembly Language');
insert into books VALUES ('0805317554', 'Elmasri and Navathe', 'Fundamentals of Database   Systems', 75.95, 'Database Fundamentals');
insert into books VALUES ('0471105597', 'Halliday, Resnick, and Walker', 'Fundamentals of   Physics Extended', 99.95, 'Physics');
insert into books VALUES ('0471587192', 'Salas and Hilles', 'Calculus: One and Several   Variables',122.15, 'Mathmatics');
insert into books VALUES ('0671032658', 'King, Stephen', 'Green Mile, The', 7.99,    'Horror');
insert into books VALUES ('0935112510', 'Clarke, Greg', 'Golf Rules Illustrated', 19.95,   'Sports');
insert into books VALUES ('0811826848', 'The Beatles', 'Beatles Anthology, The', 59.95,         'Biographies');
insert into books VALUES ('039914563X', 'Clancy, Tom', 'Bear and the Dragon, The', 28.95, 
                          'Mystery and Thrillers');
insert into books VALUES ('0316769487', 'Salinger, J.D.', 'Catcher in the Rye, The',   5.99, 'Literature and Fiction');
insert into books VALUES ('0446310783', 'Lee, Harper', 'To Kill a Mockingbird', 6.99, 
                          'Literature and Fiction');
insert into books VALUES ('0684801523', 'Fitzgerald, F. Scott', 'Great Gatsby', 11.95, 
                          'Literature and Fiction');
insert into books VALUES ('0399501487', 'Golding, William Gerald', 'Lord of the Flies: A   Novel', 6.95, 'Literature and Fiction');


--NAME: Eddie Heinz
insert into books values('1861003412', 'Wrox Press', 'Beginning XML programming', 30.99, 'XML');
insert into books values('0735610207', 'Microsoft Press', 'XML Step by Step with CDROM', 39.49, 'XML');
insert into books values('1861003110', 'Wrox Press', 'Professional XML', 40.99, 'XML');
insert into books values('1565927095', 'Robert Eckstein', 'XML Pocket Reference', 7.86, 'XML');
insert into books values('0789722429', 'Benoit Marchal', 'XML by Example', 17.99, 'XML');
insert into books values('0393972887', 'Michael Munowitz', 'Principles of Chemistry', 104.25, 'Chemistry');
insert into books values('0471597619', 'Gary D. Christian','Analytical Chemistry', 103.00, 'Chemistry');
insert into books values('0030303370', 'William Rife', 'Essentials of Chemistry', 79.55, 'Chemistry');
insert into books values('0030059380', 'Douglas A. Skooq', 'Fundamentals of Analytical Chemistry', 118.50, 'Chemistry');
insert into books values('093570261x', 'Roger L. Dekock', 'Chemical Structure and Bonding', 36.55, 'Chemistry');
insert into books values('1565926269', 'Steven Roman', 'Access Database Design  Programming', 27.01, 'Database');
insert into books values('0138613370', 'Jeffrey D. Ullman', 'A First Course in Database Systems', 65.00, 'Database');
insert into books values('0201709287', 'C.J. Date, Hugh Darwen', 'Foundation for Future Database Systems: The Third Manifesto', 39.95, 'Database');
insert into books values('0750650869', 'David Howe', 'Data Analysis for Database Design', 32.95, 'Database');

--NAME: Li Lei
--Thrillers subject
insert into books values ('0345419758','Mass Market','Air Force One Has Landed',5.99,'Thrillers');
insert into books values ('1557044287','Ridley Scott','Gladiator ',26.36,'Thrillers');
insert into books values ('0553575538','Kay Hooper','Stealing Shadows',6.5,'Thrillers');
insert into books values ('0743215052','Le Carre, John','The Constant Gardener',28,'Thrillers');
insert into books values ('0671047310','Vince Flynn','The Third Option ',24.95,'Thrillers');
--Romance subject
insert into books values ('0312965095','Kathleen Kane','This Time for Keeps',5.99,'Romance');
insert into books values ('0505523078','Ann Lawrence','Virtual Heaven',5.99,'Romance');
insert into books values ('0821762559','Quinn Taylor Evans','Daughter of Camelot ',5.99,'Romance');
insert into books values ('0517707950','Esquivel, Laura','The Law of Love',79.98,'Romance');
insert into books values ('0553577476','Leslie Lafoy','Lady Reckless ',5.50,'Romance');
--Animals subject
insert into books values ('0531164497','Ann O. Squire','Spiders of North America',6.95,'Animals');
insert into books values ('1552047210','James Herriot','James Herriots Favorite Dog Stories ',29.99,'Animals');
insert into books values ('1581950098','Kurt Johnson, Steven L. Coates','Nabokovs Blues : The Scientific Odyssey of a Literary Genius',27,'Animals');
insert into books values ('0689813813','Patricia Mullins','One Horse Waiting for Me',16,'Animals');
insert into books values ('0738204374','Steven M. Wise','Rattling the Cage : Toward Legal Rights for Animals',17.50,'Animals');

--NAME: Jian Gu
--  isbn varchar2(15),
--  author varchar2(100) not null,
--  title varchar2(128) not null, 
--  price number(7,2) not null,   
--  subject varchar2(30) not null,

-- ART
insert into books VALUES ('0810961695', 'Edward Steichen', 'The Family of Man',15.96, 'Art');
insert into books VALUES ('0671880756', 'Thomas Hoving', 'Making the Mummies Dance',21.95, 'Art');
insert into books VALUES ('0810936852', 'Peter H Hassrick ','The Georgia O_Keeffe Museum',28.00, 'Art');
insert into books VALUES ('0789305003', 'Los Angeles County Museum of Art', 'California Pop-Up Book',36.00, 'Art');
insert into books VALUES ('1878529234', 'Craig Clunas', 'Chinese Furniture',45.00, 'Art');

-- FOOD
insert into books VALUES ('0967697603 ', 'Mercedes Lee ', 'Seafood Lovers Almanac',19.95 , 'Food');
insert into books VALUES ('0688161995', 'Chris Schlesinger', 'How to Cook Meat',28.00 , 'Food');   
insert into books VALUES ('0811716937 ', 'Jerry Predika', 'The Sausage Making Cookbook',14.36 , 'Food');
insert into books VALUES ('0688127371', 'James A. Peterson', 'Fish and  Shellfish', 32.00, 'Food');
insert into books VALUES ('0882664778', 'Charles G. Reavis, ', 'Home Sausage Making',11.96 , 'Food');

-- Chemical Engineering
insert into books VALUES ('0070498415 ', 'Robert H. Perry', 'Perrys Chemical Engineers Handbook', 150.00, 'Engineering');
insert into books VALUES ('0120594757', 'Neal G. Anderson', 'Practical Process Research and  Development',89.95,
'Engineering');
insert into books VALUES ('0070571864 ', 'Gershon J. Shugar', 'Chemical Technicians Ready Reference Handbook',89.95 ,
'Engineering');
insert into books VALUES ('0471534781', 'Richard M. Felder', 'Elementary Principles of Chemical Processes', 111.95,
'Engineering');
insert into books VALUES ('0070349096', 'Henry Z. Kister', 'Distillation Design', 79.95, 'Engineering');

--NAME: Christopher Cox
--
insert into books values ('0672314800', 'Dave Taylor and James C. Armstrong', 
'Sams Teach Yourself UNIX in 24 Hours, Second Edition', 19.99, 'Computer 
Science'); 

insert into books values ('0137566107', 'Peter Abel', 'IBM PC Assembly 
Language and Programming, Fourth Edition', 63.95, 'Computer Science'); 

insert into books values ('020165783X', 'Martin Fowler with Kendall Scott' , 
'UML Distilled, Second Edition',  29.95, 'Computer Science'); 

insert into books values ('0070121430', 'Thomas H. Cormen, Charles E. 
Leiserson, and Ronald L. Rivest' , ' Introduction to Algorithms',  69.95, 
'Computer Science'); 

insert into books values ('0134897250', 'Bernd Bruegge and Alan H. Dutoit' , 
'Object Oriented Software Engineering, Conquering Complex and Changing 
Systems',  45.00,
'Computer Science');

insert into books values ('042510107X', 'Tom Clancy' , 'Red Storm Rising', 
7.99, 'Mystery'); 

insert into books values ('0425133540', 'Tom Clancy' , 'The Sum of All 
Fears', 7.99, 'Mystery'); 

insert into books values ('0425143325', 'Tom Clancy' , 'Without Remorse', 
7.99, 'Mystery');

insert into books values ('0425147584', 'Tom Clancy' , 'Debt Of Honor', 
7.99, 'Mystery'); 

insert into books values ('0870212850', 'Tom Clancy' , 'The Hunt For Red 
October', 27.95, 'Mystery');  

insert into books values ('0345384466', 'Anne Rice' , 'The Witching Hour', 
7.99, 'Horror'); 

insert into books values ('0812520610', 'Brian Lumley' , 'Blood Brothers', 
7.99, 'Horror'); 

insert into books values ('0812520629', 'Brian Lumley' , 'The Last Aerie', 
7.99, 'Horror'); 

insert into books values ('067100767X', 'V.C. Andrews' , 'Rain', 7.99, 
'Horror'); 
--
--NAME: Yong Li
insert into books values('0385479565', 'Richard Preston', 'The Hot Zone', 7.99, 'Science');
insert into books values('1864364432', 'John Ashton', 'In Six Days : Why 50 Scientists Choose to Believe in Creation', 14.95, 'Science');
insert into books values('0849323754', 'Hooman H. Rashidi', 'Bioinformatics Basics Applications in Biological Science and Medicine', 69.95, 'Science');
insert into books values('0688069711', 'Gary Selden', 'The Body Electric : Electromagnetism and the Foundation of Life', 13.00, 'Education');
insert into books values('0932813739', 'David Hatcher Childress', 'Technology of the Gods : The Incredible Sciences of the Ancients', 16.95, 'Science');
insert into books values('0805057579', 'Thomas A. Bass', 'The Predictors', 15.00, 'Science');
insert into books values('0688160999', 'Janine M. Benyus', 'Biomimicry : Innovation Inspired by Nature', 14.00, 'Science');
insert into books values('0618056777', 'Jane Goodall', 'Through a Window', 14.00, 'Science');
insert into books values('0071354190', 'Peter Lane Taylor', 'Science at the Extreme: Scientists on the Cutting Edge of Discovery', 29.95, 'Science');
insert into books values('0262181916', 'Santiago. Ramon Y Cajal', 'Advice for a Young Investigator', 21.23, 'Science');

insert into books values('0935039031', 'Michael Brown', 'Streetwise Manhattan', 5.95, 'Travel');
insert into books values('0864426429', 'Kim Grant', 'Lonely Planet Boston', 15.99, 'Travel');
insert into books values('1566912296', 'Rick Steves', 'Rick Steve Italy 2001', 17.95, 'Travel');
insert into books values('0961549890', 'Lenore W. Horowitz', 'Kauai Underground Guide', 12.95, 'Travel');
insert into books values('0395982111', 'Aglaia Kremezi', 'The Foods of the Greek Islands : Cooking and Culture at the Crossroads of the Mediterranean', 35.00, 'Travel');
insert into books values('0966625307', 'Toni Polancy', 'So You Want to Live in Hawaii', 19.95, 'Travel');
insert into books values('0789404257', 'Various', 'Eyewitness Travel Guides: Italy', 29.95, 'Travel');
insert into books values('0767903854', 'Bill Bryson', 'In a Sunburned Country', 25.00, 'Travel');
insert into books values('0120848104', 'Les Beletsky', 'Costa Rica: The Ecotraveller Wildlife Guide', 30.00, 'Travel');
insert into books values('0684869519', 'Wendy Orange', 'Coming Home To Jerusalem: A Personal Journey', 25.00, 'Travel');

insert into books values('0449911942', 'John Updike', 'Rabbit at Rest', 12.95, 'Fiction');
insert into books values('0452272971', 'Sebastien Japrisot, Linda Coverdale', 'A Very Long Engagement', 14.00, 'Fiction');
insert into books values('1573225312', 'Chang-Rae Lee', 'Native Speaker', 12.95, 'Fiction');
insert into books values('0156007754', 'Jose Saramago, Giovanni Pontiero', 'Blindness', 14.00, 'Fiction');
insert into books values('0393316009', 'Andrea Barrett', 'Ship Fever', 12.00, 'Fiction');
insert into books values('0811213668', 'W. G. Sebald, Michael Hulse', 'TThe Emigrants', 10.95, 'Fiction');
insert into books values('067976674X', 'Alice Munro', 'Selected Stories', 16.00, 'Fiction');
insert into books values('0151004714', 'Claire Messud', 'The Last Life', 24.00, 'Fiction');
insert into books values('038071115X', 'Tracy Kidder', 'The Soul of a New Machine', 12.50, 'Fiction');
insert into books values('0393314251', 'Stephen Jay Gould', 'The Mismeasure of Man', 15.95, 'Fiction');


