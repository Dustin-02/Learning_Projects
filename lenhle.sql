SELECT
    maxe,
    tentuyen,
    ngaygiochuyen,
    COUNT(*) AS SoHang
FROM
    ma_giuong_xe
WHERE
    tt = '0'
GROUP BY
    maxe, tentuyen, ngaygiochuyen;
    
SELECT *
FROM ve_xe
WHERE
    maxe = '667788'
    AND tuyendi = 'HCM-DL'
    AND ngaygiodi = '2023-02-01 08:00:00';
    
    
SELECT
    chay.maxe,
    chay.tentuyen,
    chay.ngaygiochuyen,
    magiuong.magiuong
FROM
    chay join magiuong;

DELETE FROM hanh_khach;
DELETE FROM chay;
DELETE FROM van_chuyen_hang;
SHOW TRIGGERS;
show function status;
-- -------------------------------------------------------

CALL UPDATE_KH('Nguyen Dinh ', '087020028456', '857569365', 'nguyendinhhoangminh@gmail.com', '1965-01-12', '0375998765','2');
call INSERT_KH('Nguyen Dinh Hoang Minh', '087020028456', '857569365', 'nguyendinhhoangminh@gmail.com', '1965-01-12', '0375998765');
CALL DELETE_KH('857569365');
call Hieuquahoatdong();


DROP TABLE IF EXISTS magiuong;
CREATE TABLE magiuong
(	
	magiuong	varCHAR(3)
);

SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Cap nhap thong tin khach hang thanh cong';
SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Thông báo của bạn tại đây';

INSERT INTO magiuong VALUES ('a01');
INSERT INTO magiuong VALUES ('a02');
INSERT INTO magiuong VALUES ('a03');
INSERT INTO magiuong VALUES ('a04');
INSERT INTO magiuong VALUES ('a05');
INSERT INTO magiuong VALUES ('a06');
INSERT INTO magiuong VALUES ('a07');
INSERT INTO magiuong VALUES ('a08');
INSERT INTO magiuong VALUES ('a09');
INSERT INTO magiuong VALUES ('a10');
INSERT INTO magiuong VALUES ('b01');
INSERT INTO magiuong VALUES ('b02');
INSERT INTO magiuong VALUES ('b03');
INSERT INTO magiuong VALUES ('b04');
INSERT INTO magiuong VALUES ('b05');
INSERT INTO magiuong VALUES ('b06');
INSERT INTO magiuong VALUES ('b07');
INSERT INTO magiuong VALUES ('b08');
INSERT INTO magiuong VALUES ('b09');
INSERT INTO magiuong VALUES ('b10');