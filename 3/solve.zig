const std = @import("std");
const Number = struct {
    value: u32,
    from: u32,
    to: u32,
};
fn isDigit(char: u8) bool {return char >= '0' and char <= '9';}

fn parseNumbers(nbuf: *[16]?Number, buf: [256]u8, n: usize) !void {
    var k: u32 = 0;
    var i: u32 = 0;
    while (i < n) : (i += 1) {
        if (!isDigit(buf[i])) continue;
        var j: u32 = i;
        while (isDigit(buf[i])) {i += 1;}
        nbuf[k] = Number{
            .value = try std.fmt.parseUnsigned(u32, buf[j..i], 10),
            .from = if (j > 0) j - 1 else 0,
            .to = if (i + 1 > n) i else i + 1,
        };
        k += 1;
    }
    while (k < 16) : (k += 1) nbuf[k] = null;
}

fn solve1(buffers: [3][256]u8, nbuffers: [3][16]?Number) !u32 {
    var bufSym: [256]bool = undefined;
    for (buffers) |wbuffer| for (wbuffer, 0..) |char, i| {
        if (!isDigit(char) and char != '.' and char != 170) bufSym[i] = true;
    };
    var sum: u32 = 0;
    for (nbuffers[1]) |number| if (number) |num| for (num.from..num.to) |k| {
        if (bufSym[k]) sum += num.value;
    };
    return sum;
}

fn solve2(buffers: [3][256]u8, nbuffers: [3][16]?Number) !u32 {
    var sum: u32 = 0;
    for (buffers[1], 0..) |char, i| if (char == '*') {
        var k: u8 = 0;
        var power: u32 = 1;
        for (nbuffers) |nbuffer| for (nbuffer) |number| if (number) |num| {
            if (i >= num.from and i < num.to) {
                k += 1;
                power *= num.value;
            }
        };
        if (k == 2) sum += power;
    };
    return sum;
}

pub fn main() !void {
    const stdin = std.io.getStdIn().reader();
    var buffers: [3][256]u8 = undefined;
    var nbuffers: [3][16]?Number = undefined;
    const n = (try stdin.readUntilDelimiterOrEof(&buffers[1], '\n')).?.len;
    try parseNumbers(&nbuffers[1], buffers[1], n);

    var sum1: u32 = 0;
    var sum2: u32 = 0;
    var quit = false;
    while (!quit) {
        quit = try stdin.readUntilDelimiterOrEof(&buffers[2], '\n') == null;
        if (quit) buffers[2] = undefined;
        try parseNumbers(&nbuffers[2], buffers[2], n);
        sum1 += try solve1(buffers, nbuffers);
        sum2 += try solve2(buffers, nbuffers);
        buffers = [3][256]u8{ buffers[1], buffers[2], buffers[0] };
        nbuffers = [3][16]?Number{ nbuffers[1], nbuffers[2], nbuffers[0] };
    }
    std.debug.print("{}\n", .{sum1});
    std.debug.print("{}\n", .{sum2});
}
