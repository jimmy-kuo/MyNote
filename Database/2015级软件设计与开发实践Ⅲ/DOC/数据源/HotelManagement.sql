/*
 Navicat Premium Data Transfer

 Source Server         : tencentcloud @ 182
 Source Server Type    : MySQL
 Source Server Version : 80011
 Source Host           : 118.126.104.182:3306
 Source Schema         : HotelManagement

 Target Server Type    : MySQL
 Target Server Version : 80011
 File Encoding         : 65001

 Date: 20/08/2018 21:40:21
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for roombooking
-- ----------------------------
DROP TABLE IF EXISTS `roombooking`;
CREATE TABLE `roombooking`  (
  `uid` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `rid` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `sdate` datetime(0) NULL,
  `edate` datetime(0) NULL,
  `user` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `remark` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `roomername` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `roomertel` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  INDEX `FK_bookingroom`(`uid`, `rid`) USING BTREE,
  INDEX `FK_bookuser`(`uid`, `user`) USING BTREE,
  CONSTRAINT `FK_bookingroom` FOREIGN KEY (`uid`, `rid`) REFERENCES `roominfo` (`uid`, `rid`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `FK_bookuser` FOREIGN KEY (`uid`, `user`) REFERENCES `users` (`uid`, `user`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of roombooking
-- ----------------------------
INSERT INTO `roombooking` VALUES ('如家', '100', '2019-07-01 14:00:00', '2019-07-15 12:00:00', 'houjie', '勿扰', '侯捷', '13176244325');
INSERT INTO `roombooking` VALUES ('如家', '2001', '2018-09-15 14:00:00', '2018-09-17 12:00:00', 'houjie', '哈工大校招', '校招团队', 'Tencent');
INSERT INTO `roombooking` VALUES ('如家', '2002', '2018-09-15 14:00:00', '2018-09-17 12:00:00', 'houjie', '哈工大校招', '校招团队', 'Tencent');
INSERT INTO `roombooking` VALUES ('如家', '3001', '2018-09-15 14:00:00', '2018-09-17 12:00:00', 'houjie', '哈工大校招', '校招团队', 'Tencent');

-- ----------------------------
-- Table structure for roomcheck
-- ----------------------------
DROP TABLE IF EXISTS `roomcheck`;
CREATE TABLE `roomcheck`  (
  `uid` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `rid` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `sdate` datetime(0) NULL,
  `edate` datetime(0) NULL,
  `user` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `remark` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `roomername` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `roomertel` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `roomerid` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `price` int(11) NOT NULL,
  INDEX `FK_checkroom`(`uid`, `rid`) USING BTREE,
  INDEX `FK_checkuser`(`uid`, `user`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of roomcheck
-- ----------------------------
INSERT INTO `roomcheck` VALUES ('如家', '3001', '2018-08-20 14:00:00', '2018-08-21 12:00:00', 'houjie', '4', '1', '2', '3', 98);
INSERT INTO `roomcheck` VALUES ('如家', '2001', '2018-08-20 14:00:00', '2018-08-24 12:00:00', 'houjie', '44', '11', '22', '33', 198);
INSERT INTO `roomcheck` VALUES ('如家', '2002', '2018-08-20 14:00:00', '2018-08-24 12:00:00', 'houjie', '44', '11', '22', '33', 123123);
INSERT INTO `roomcheck` VALUES ('如家', '3002', '2018-08-20 14:00:00', '2018-08-24 12:00:00', 'houjie', '44', '11', '22', '33', 98);
INSERT INTO `roomcheck` VALUES ('如家', '3002', '2018-08-20 21:07:10', '2018-08-31 21:07:14', 'houjie', '3', '4', '5', '3', 2323);
INSERT INTO `roomcheck` VALUES ('如家', '100', '2018-08-20 14:00:00', '2018-08-22 12:00:00', 'houjie', '4', '111', '222', '333', 998);

-- ----------------------------
-- Table structure for roominfo
-- ----------------------------
DROP TABLE IF EXISTS `roominfo`;
CREATE TABLE `roominfo`  (
  `uid` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `rid` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `roomtype` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
  `roomprice` int(11) NOT NULL,
  `updatetime` timestamp(0) NULL DEFAULT CURRENT_TIMESTAMP,
  `remark` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  PRIMARY KEY (`uid`, `rid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of roominfo
-- ----------------------------
INSERT INTO `roominfo` VALUES ('如家', '100', '总统套房', 998, '2018-08-20 19:12:10', '');
INSERT INTO `roominfo` VALUES ('如家', '1000', '豪华套房', 499, '2018-08-20 19:12:41', '');
INSERT INTO `roominfo` VALUES ('如家', '2001', '双人间', 198, '2018-08-20 19:12:56', '');
INSERT INTO `roominfo` VALUES ('如家', '2002', '双人间', 198, '2018-08-20 19:13:12', '');
INSERT INTO `roominfo` VALUES ('如家', '3001', '大床房', 98, '2018-08-20 19:13:29', '');
INSERT INTO `roominfo` VALUES ('如家', '3002', '大床房', 98, '2018-08-20 19:13:52', '空调损坏');
INSERT INTO `roominfo` VALUES ('如家', '3003', '小时房', 50, '2018-08-20 19:14:24', '');
INSERT INTO `roominfo` VALUES ('威海格林豪泰酒店', '101', '大床房', 188, '2018-05-28 22:07:57', '');

-- ----------------------------
-- Table structure for roomstate
-- ----------------------------
DROP TABLE IF EXISTS `roomstate`;
CREATE TABLE `roomstate`  (
  `uid` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `rid` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `state` int(11) NOT NULL DEFAULT 0,
  `roomername` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
  `roomertel` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `remark` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  PRIMARY KEY (`uid`, `rid`) USING BTREE,
  CONSTRAINT `FK_room` FOREIGN KEY (`uid`, `rid`) REFERENCES `roominfo` (`uid`, `rid`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of roomstate
-- ----------------------------
INSERT INTO `roomstate` VALUES ('如家', '100', 1, '111', '222', '4');
INSERT INTO `roomstate` VALUES ('如家', '1000', 0, '', NULL, NULL);
INSERT INTO `roomstate` VALUES ('如家', '2001', 1, '11', '22', '44');
INSERT INTO `roomstate` VALUES ('如家', '2002', 0, '', '', '');
INSERT INTO `roomstate` VALUES ('如家', '3001', 0, '', '', '');
INSERT INTO `roomstate` VALUES ('如家', '3002', 0, '', '', '');
INSERT INTO `roomstate` VALUES ('如家', '3003', 0, '', NULL, NULL);
INSERT INTO `roomstate` VALUES ('威海格林豪泰酒店', '101', 1, 'heizhou', '17863130096', '不要打扰');

-- ----------------------------
-- Table structure for users
-- ----------------------------
DROP TABLE IF EXISTS `users`;
CREATE TABLE `users`  (
  `uid` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `user` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `password` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `roles` int(11) NOT NULL,
  PRIMARY KEY (`uid`, `user`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of users
-- ----------------------------
INSERT INTO `users` VALUES ('如家', 'hitwh', '1234', 2);
INSERT INTO `users` VALUES ('如家', 'houjie', 'houjie', 2);
INSERT INTO `users` VALUES ('如家', 'root', 'test', 1);
INSERT INTO `users` VALUES ('如家', 'test', 'test', 2);
INSERT INTO `users` VALUES ('威海格林豪泰酒店', 'root', '123456', 1);
INSERT INTO `users` VALUES ('威海格林豪泰酒店', 'wangmei', '123456', 2);

SET FOREIGN_KEY_CHECKS = 1;
