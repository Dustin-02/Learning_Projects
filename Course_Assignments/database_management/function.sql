USE quanlyvexe;
DROP FUNCTION KPI_tuyen_xe;

DELIMITER $$
CREATE FUNCTION KPI_tuyen_xe(
    ngay_input DATE,
    tb_input DECIMAL(10,2)
)
RETURNS TEXT
DETERMINISTIC
BEGIN
    DECLARE result TEXT DEFAULT '';
    DECLARE done INT DEFAULT FALSE;
    DECLARE tentuyen VARCHAR(30);
    DECLARE trungbinh_doanhthu DECIMAL(10,2);
    DECLARE cur CURSOR FOR 
        SELECT
            chuyen.tentuyen,
            SUM(ve_xe.tongtien) / COUNT(DISTINCT ve_xe.maxe)
        FROM
            ve_xe
            JOIN chuyen ON ve_xe.tuyendi = chuyen.tentuyen AND ve_xe.ngaygiodi = chuyen.ngaygio
        WHERE
            DATE(ve_xe.thoigiandatve) = ngay_input
        GROUP BY
            chuyen.tentuyen
        HAVING
            SUM(ve_xe.tongtien) / COUNT(DISTINCT ve_xe.maxe) > tb_input;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

    OPEN cur;

    read_loop: LOOP
        FETCH cur INTO tentuyen, trungbinh_doanhthu;
        IF done THEN
            LEAVE read_loop;
        END IF;
        SET result = CONCAT(result, tentuyen, ',', trungbinh_doanhthu, '; ');
    END LOOP;

    CLOSE cur;
    RETURN result;
END$$
DELIMITER ;

SELECT KPI_tuyen_xe('2023-01-19', 10.00);


/* check cost nhan su */
DROP FUNCTION check_cost_nhan_su;

DELIMITER $$
CREATE FUNCTION check_cost_nhan_su(
  thang_input INT,
  nam_input INT,
  tyle_input DECIMAL(10,2)
)
RETURNS BOOLEAN
DETERMINISTIC
BEGIN
  SET @tong_doanh_thu = 0;
  SET @tong_cost_nv = 0;
  IF (thang_input > 0 AND thang_input < 13) AND (nam_input > 1900 AND nam_input < 2024) THEN
    SELECT SUM(nhan_vien.luongcoban + nhan_vien.luongthuong) INTO @tong_cost_nv
        FROM nhan_vien
        WHERE (YEAR(nhan_vien.ngaybatdau) < nam_input)
			OR (YEAR(nhan_vien.ngaybatdau) = nam_input AND MONTH(nhan_vien.ngaybatdau) <= thang_input);
    SELECT SUM(tong_doanh_thu) INTO @tong_doanh_thu
    FROM (
      SELECT SUM(tongtien) AS tong_doanh_thu FROM ve_xe WHERE MONTH(thoigiandatve) = thang_input AND YEAR(thoigiandatve) = nam_input
      UNION ALL
      SELECT SUM(chiphi) AS tong_doanh_thu FROM van_chuyen_hang, ve_xe WHERE ve_xe.masove=van_chuyen_hang.masove AND MONTH(thoigiandatve) = thang_input AND YEAR(thoigiandatve) = nam_input
    ) AS bang_doanhthu;
      RETURN @tong_cost_nv/@tong_doanh_thu*100 > tyle_input;
  ELSE
    RETURN false;
  END IF;
END$$
DELIMITER ;


SELECT check_cost_nhan_su(1, 2023, 10.00);
