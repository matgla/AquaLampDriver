#include "display/images.hpp"

#include <gsl/span>

namespace display
{

/**
 * @brief Empty triangle image
 * width = 4, height = 7
 * 1000
 * 1100
 * 1010
 * 1001
 * 1010
 * 1100
 * 1000
 **/
const uint8_t emptyTriangleImage[4] = {
    0b11111110,
    0b01000100,
    0b00101000,
    0b00010000};

Image Images::emptyTriangle = {
    4,
    7,
    gsl::span<const uint8_t>{emptyTriangleImage}};

/**
 * @brief Full triangle image
 * width = 4, height = 7
 * 1000
 * 1100
 * 1110
 * 1111
 * 1110
 * 1100
 * 1000
 **/
const uint8_t fullTriangleImage[4] = {
    0b11111110,
    0b01111100,
    0b00111000,
    0b00010000};

Image Images::fullTriangle = {
    4,
    7,
    gsl::span<const uint8_t>{fullTriangleImage}};

/**
 * @brief Bulb image
 * width = 5, height = 7
 * 01110
 * 10001
 * 10001
 * 10001
 * 01110
 * 01110
 * 00100
 **/
const uint8_t bulbImage[5] = {
    0b01110000,
    0b10001100,
    0b10001110,
    0b10001100,
    0b0111000};

Image Images::bulb = {
    5,
    7,
    gsl::span<const uint8_t>{bulbImage}};

/**
 * @brief Back icon
 * 0111111111111111110
 * 1100111011000101011
 * 1101010101011101011
 * 1100110001011100111
 * 1101010101011101011
 * 1100110101000101011
 * 0111111111111111110
 **/
const uint8_t backIconImage[19] = {
    0b01111100,
    0b11111110,
    0b10000010,
    0b10101010,
    0b11010110,
    0b11111110,
    0b11000010,
    0b10101110,
    0b11000010,
    0b11111110,
    0b10000010,
    0b10111010,
    0b10111010,
    0b11111110,
    0b10000010,
    0b11101110,
    0b10010010,
    0b11111110,
    0b01111100};

Image Images::backIcon = {
    19,
    7,
    gsl::span<const uint8_t>{backIconImage}};

/**
 * @brief Select icon
 * 0111111111111111110
 * 1111000100010111111
 * 1111011101110111111
 * 1111000100110111111
 * 1111110101110111111
 * 1111000100010001111
 * 0111111111111111110
 **/
const uint8_t selectIconImage[19] = {
    0b01111100,
    0b11111110,
    0b11111110,
    0b11111110,
    0b10001010,
    0b10101010,
    0b10100010,
    0b11111110,
    0b10000010,
    0b10101010,
    0b10111010,
    0b11111110,
    0b10000010,
    0b11111010,
    0b11111010,
    0b11111110,
    0b11111110,
    0b11111110,
    0b01111100};

Image Images::selectIcon = {
    19,
    7,
    gsl::span<const uint8_t>{selectIconImage}};

/**
 * @brief Filled arrow down
 *
 * 00000
 * 00000
 * 00000
 * 11111
 * 01110
 * 00100
 * 00000
 **/

const uint8_t arrowDownImage[5] = {
    0b00010000,
    0b00011000,
    0b00011100,
    0b00011000,
    0b00010000};

Image Images::ArrowDown = {
    5,
    7,
    gsl::span<const uint8_t>{arrowDownImage}};

/**
 * @brief Filled arrow up
 *
 * 00000
 * 00100
 * 01110
 * 11111
 * 00000
 * 00000
 * 00000
 **/
const uint8_t arrowUpImage[5] = {
    0b00010000,
    0b00110000,
    0b01110000,
    0b00110000,
    0b00010000};

Image Images::ArrowUp = {
    5,
    7,
    gsl::span<const uint8_t>{arrowUpImage}};

/**
 * @brief Mosaic for making frames
 *
 * 0 1
 * 1 0
 * 0 1
 * 1 0
 * 0 1
 * 1 0
 * 0 1
 **/
const uint8_t chessboardMosaic[2] = {
    0b01010100,
    0b10101010};

Image Images::ChessboardMosaic = {
    2,
    7,
    gsl::span<const uint8_t>{chessboardMosaic}};

} // namespace display
