
-- DELIMITER $$
-- CREATE FUNCTION KPI_tuyen_xe(
--     in ngay_input date,
--     @tb_input DECIMAL(10,2)
-- )
-- RETURNS TABLE
-- AS
-- RETURN
-- (
--     SELECT
--         chuyen.tentuyen AS tentuyen,
--         SUM(ve_xe.tongtien) AS tong_doanhthu,
--         COUNT(DISTINCT ve_xe.maxe) AS soluongxe,
--         SUM(ve_xe.tongtien) / COUNT(DISTINCT ve_xe.maxe) AS trungbinh_doanhthu
--     FROM
--         ve_xe
--         JOIN chuyen ON ve_xe.tuyendi = chuyen.tentuyen AND ve_xe.ngaygiodi = chuyen.ngaygio
--     WHERE
--         ve_xe.thoigiandatve >= @ngay_input
--     GROUP BY
--         chuyen.tentuyen
--     HAVING
--         SUM(ve_xe.tongtien) / COUNT(DISTINCT ve_xe.maxe) > @tb_input
-- );
-- DELIMITER ;

DROP procedure IF EXISTS KPI_tuyen_xe;
DELIMITER $$

CREATE PROCEDURE KPI_tuyen_xe(
    IN ngay_input DATE,
    IN tb_input DECIMAL(10,2),
    OUT tentuyen VARCHAR(30),
    OUT tong_doanhthu DECIMAL(10,2),
    OUT soluongxe INT,
    OUT trungbinh_doanhthu DECIMAL(10,2)
)
BEGIN
    SELECT
        chuyen.tentuyen,
        SUM(ve_xe.tongtien),
        COUNT(DISTINCT ve_xe.maxe),
        SUM(ve_xe.tongtien) / COUNT(DISTINCT ve_xe.maxe)
    INTO
        tentuyen, tong_doanhthu, soluongxe, trungbinh_doanhthu
    FROM
        ve_xe
        JOIN chuyen ON ve_xe.tuyendi = chuyen.tentuyen AND ve_xe.ngaygiodi = chuyen.ngaygio
    WHERE
        ve_xe.thoigiandatve >= ngay_input
    GROUP BY
        chuyen.tentuyen
    HAVING
        SUM(ve_xe.tongtien) / COUNT(DISTINCT ve_xe.maxe) > tb_input;
END $$

DELIMITER ;

call KPI_tuyen_xe("2023-2-1", 500000.00)







-- SELECT *
-- FROM KPI_tuyen_xe('2023-11-30', 1000.00);

-- CREATE FUNCTION check_cost_nhan_su(
--     thang_input INT,
--     nam_input INT,
--     tyle_input DECIMAL(10,2)
-- )
-- RETURNS BOOLEAN
-- BEGIN
--     DECLARE tong_cost_nv DECIMAL(10,2);
--     DECLARE tong_doanh_thu DECIMAL(10,2);
--     IF (thang_input BETWEEN 1 AND 12) AND (nam_input BETWEEN 1900 AND 2023) THEN
--         SELECT SUM(nhan_vien.luongcoban + nhan_vien.luongthuong) INTO tong_cost_nv
--         FROM nhan_vien
--         WHERE MONTH(nhan_vien.ngaybatdau) <= thang_input
--             AND YEAR(nhan_vien.ngaybatdau) <= nam_input;
--         SELECT SUM(tong_doanh_thu) INTO tong_doanh_thu
--         FROM (
--             SELECT SUM(tongtien) AS tong_doanh_thu FROM ve_xe WHERE MONTH(ngaygiodi) = thang_input AND YEAR(ngaygiodi) = nam_input
--             UNION ALL
--             SELECT SUM(chiphi) AS tong_doanh_thu FROM van_chuyen_hang, ve_xe WHERE masove=masove AND MONTH(thoigiandatve) = thang_input AND YEAR(thoigiandatve) = nam_input
--         ) AS bang_doanhthu;
--         RETURN (tong_cost_nv / tong_doanh_thu * 100) > tyle_input;
--     ELSE
--         RETURN false;
--     END IF;
-- END;

-- SELECT *
-- FROM check_cost_nhan_su('10', 1997, 30);
