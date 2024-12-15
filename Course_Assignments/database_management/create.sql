DROP TABLE IF EXISTS Khach_hang, tram, xe, nhan_vien, ban_ve, tai_xe, tuyen, chuyen, ve_xe, hanh_khach, van_chuyen_hang, Chay, di_qua, ma_giuong, ma_giuong_xe, KTGCT;
	CREATE TABLE Khach_hang 
(	hovaten		VARCHAR(30)	NOT NULL,
	cccd		varCHAR(12)  UNIQUE,					
	maKH		varCHAR(9)	PRIMARY KEY,
	Email	VARCHAR(50),
	ngaysinh		date,
	sdt	varchar(10),
	trang_thai varchar(1) DEFAULT '0'
);
CREATE TABLE tram
(	tentram		varCHAR(1) PRIMARY KEY	,
	dia_chi	varCHAR(30),
	quanly  varCHAR(9) NOT NULL
);


CREATE TABLE xe
(	masoxe		varCHAR(6) PRIMARY KEY	,
	biensoxe	varCHAR(5) UNIQUE,
	loaixe	VARCHAR(10) NOT NULL,
	tonggiuong char(2),
	khoiluonghangvc INT	
);

CREATE TABLE nhan_vien
(	hovaten		VARCHAR(30)	NOT NULL,
	cccd		varCHAR(12),					
	maNV		varCHAR(9)	PRIMARY KEY,
	Email	VARCHAR(50),
	ngaysinh		date,
	luongcoban	DECIMAL(10,2),
	luongthuong	DECIMAL(10,2),
	ngaybatdau		date,
	sdt	varchar(10)
);	
CREATE TABLE ban_ve
(	maNV		varCHAR(9)PRIMARY KEY,
	calam	VARCHAR(1) NOT NULL,
	quanly  varCHAR(9),
	tentram		varCHAR(1),
	CONSTRAINT		banve_nv	FOREIGN KEY (maNV)
				REFERENCES nhan_vien(maNV)
				ON DELETE CASCADE,
	CONSTRAINT		tram_nv	FOREIGN KEY (tentram)
				REFERENCES tram(tentram)
				ON DELETE CASCADE
);
/*CONSTRAINT quanly-nhan ve,CONSTRAINT quanly-tram*, tentram-ten tram*/


CREATE TABLE tai_xe
(	maNV		varCHAR(9)	PRIMARY KEY,
	maxe		varchar(6),
	banglai	VARCHAR(1) NOT NULL,
	SNKN		CHAR(2),
	CONSTRAINT		taixe_nv	FOREIGN KEY (maNV)
				REFERENCES nhan_vien(maNV)
				ON DELETE CASCADE,
	CONSTRAINT		taixe_xe	FOREIGN KEY (maxe)
				REFERENCES xe(masoxe)
				ON DELETE CASCADE
);

CREATE TABLE tuyen
(	tentuyen		varCHAR(30) PRIMARY KEY	,
	mota	varCHAR(30)	
);


CREATE TABLE chuyen
(	tentuyen		varCHAR(30)	,
	ngaygio  datetime,
	PRIMARY KEY(tentuyen,ngaygio),
	CONSTRAINT		chuyen_tuyen	FOREIGN KEY (tentuyen)
				REFERENCES tuyen(tentuyen)
				ON DELETE CASCADE
);



CREATE TABLE ve_xe
(	masove		varCHAR(9) PRIMARY KEY	,
	tramdi	VARCHAR(1) NOT NULL,
	tramden	VARCHAR(1) NOT NULL,
	tuyendi varchar(30),
	ngaygiodi  datetime,
	maxe varchar(6),
	maKH	varchar(9),
	manv	varCHAR(9) ,
	thoigiandatve datetime,
	tongtien DECIMAL(10,2),
	CONSTRAINT	KH_dat	FOREIGN KEY (maKH)
				REFERENCES khach_hang(maKH)
				ON DELETE CASCADE,
	CONSTRAINT	nhanvien_dat	FOREIGN KEY (manv)
				REFERENCES ban_ve(maNV)
				ON DELETE CASCADE,
	CONSTRAINT	vexe_xe	FOREIGN KEY (maxe)
				REFERENCES xe(masoxe)
				ON DELETE CASCADE,
	/*CONSTRAINT	vexe_tramdi	FOREIGN KEY (tramdi)
				REFERENCES tram(tentram)
				ON DELETE CASCADE,
	CONSTRAINT	vexe_tramden	FOREIGN KEY (tramden)
				REFERENCES tram(tentram)
				ON DELETE CASCADE,*/
	CONSTRAINT	vexe_tuyendi	FOREIGN KEY (tuyendi,ngaygiodi)
				REFERENCES chuyen(tentuyen,ngaygio)
				ON DELETE CASCADE
);




CREATE TABLE hanh_khach
(	masove		varCHAR(9) PRIMARY KEY	,
	sogiuong	int,
	CONSTRAINT		hanhkhach_vexe	FOREIGN KEY (masove)
				REFERENCES ve_xe(masove)
				ON DELETE CASCADE
);



CREATE TABLE van_chuyen_hang
(	masove		varCHAR(9) PRIMARY KEY	,
	SDTnguoinhan	varCHAR(10) NOT NULL,
	tennguoinhan	varCHAR(30),
	khoiluong		int,
	dai		float,
	rong		float,
	cao		float,
	luuy			varchar(20),
	chiphi			DECIMAL(10,2),
	CONSTRAINT		vanchuyenhang_vexe	FOREIGN KEY (masove)
				REFERENCES ve_xe(masove)
				ON DELETE CASCADE
);


CREATE TABLE Chay
(	maxe		varCHAR(6) ,
	tentuyen varchar(30),
	ngaygiochuyen  datetime,
    giuongtrong decimal(2,0),
	PRIMARY KEY(maxe,tentuyen,ngaygiochuyen),
	CONSTRAINT	chay_xe	FOREIGN KEY (maxe)
				REFERENCES xe(masoxe)
				ON DELETE CASCADE,
	CONSTRAINT	chay_chuyen	FOREIGN KEY (tentuyen,ngaygiochuyen)
				REFERENCES chuyen(tentuyen,ngaygio)
				ON DELETE CASCADE
);


CREATE TABLE di_qua
(	tentram		varCHAR(1),
	tentuyen varchar(30),
	thutu  int,
	gia DECIMAL(10,2),
	PRIMARY KEY(tentram,tentuyen),
	CONSTRAINT	diqua_tram	FOREIGN KEY (tentram)
				REFERENCES tram(tentram)
				ON DELETE CASCADE,
	CONSTRAINT	ditrong_tuyen	FOREIGN KEY (tentuyen)
				REFERENCES tuyen(tentuyen)
				ON DELETE CASCADE
);


CREATE TABLE ma_giuong
(	mave varchar(9),
	magiuong		varCHAR(3) ,
	PRIMARY KEY(mave,magiuong),
	CONSTRAINT	magiuong_ve	FOREIGN KEY (mave)
				REFERENCES ve_xe(masove)
				ON DELETE CASCADE

);

CREATE TABLE ma_giuong_xe
(	magiuong		varCHAR(3) ,
	maxe varchar(6),
    tentuyen varCHAR(30),
    ngaygiochuyen datetime,
    tt varchar(1),
	PRIMARY KEY(magiuong, maxe,tentuyen, ngaygiochuyen),
	CONSTRAINT	ma_giuong_xe	FOREIGN KEY (maxe)
				REFERENCES xe(masoxe)
				ON DELETE CASCADE,
	CONSTRAINT	ma_giuong_chuyen	FOREIGN KEY (tentuyen,ngaygiochuyen)
				REFERENCES chuyen(tentuyen,ngaygio)
				ON DELETE CASCADE
);
CREATE TABLE KTGCT
( tentuyen varCHAR(30) ,
giuatram varchar(3),
sogio int,
PRIMARY KEY(tentuyen,giuatram,sogio),
CONSTRAINT KTGCT_tuyen FOREIGN KEY (tentuyen)
REFERENCES tuyen(tentuyen)
ON DELETE CASCADE
);

DROP TABLE IF EXISTS magiuong;
CREATE TABLE magiuong
(	
	magiuong	varCHAR(3),
    tt varchar(1)
);

INSERT INTO magiuong VALUES ('a01','0');
INSERT INTO magiuong VALUES ('a02','0');
INSERT INTO magiuong VALUES ('a03','0');
INSERT INTO magiuong VALUES ('a04','0');
INSERT INTO magiuong VALUES ('a05','0');
INSERT INTO magiuong VALUES ('a06','0');
INSERT INTO magiuong VALUES ('a07','0');
INSERT INTO magiuong VALUES ('a08','0');
INSERT INTO magiuong VALUES ('a09','0');
INSERT INTO magiuong VALUES ('a10','0');
INSERT INTO magiuong VALUES ('b01','0');
INSERT INTO magiuong VALUES ('b02','0');
INSERT INTO magiuong VALUES ('b03','0');
INSERT INTO magiuong VALUES ('b04','0');
INSERT INTO magiuong VALUES ('b05','0');
INSERT INTO magiuong VALUES ('b06','0');
INSERT INTO magiuong VALUES ('b07','0');
INSERT INTO magiuong VALUES ('b08','0');
INSERT INTO magiuong VALUES ('b09','0');
INSERT INTO magiuong VALUES ('b10','0');
