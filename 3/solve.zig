const std = @import("std");
const Number = struct { value: usize, from: u32, to: u32 };

fn parseNumbers(nbuf: *[16]?Number, buf: [256]u8, n: usize) !void {
    var k: u32 = 0;
    var i: u32 = 0;
    while (i < n) : (i += 1) {
        var parser = std.fmt.Parser{ .buf = buf[i..] };
        const number = parser.number() orelse continue;
        const from = if (i > 0) i - 1 else 0;
        i += std.math.log10_int(number) + 1;
        nbuf[k] = Number{ .value = number, .from = from, .to = @min(n, i + 1) };
        k += 1;
    }
    while (k < 16) : (k += 1) nbuf[k] = null;
}

fn solve1(buffers: [3][256]u8, nbuffers: [3][16]?Number) !usize {
    var bufSym: [256]bool = undefined;
    for (buffers) |buffer| for (buffer, 0..) |char, i| switch (char) {
        '0'...'9', '.', 170 => {},
        else => {
            bufSym[i] = true;
        },
    };
    var sum: usize = 0;
    for (nbuffers[1]) |number| if (number) |num| for (num.from..num.to) |k| {
        if (bufSym[k]) sum += num.value;
    };
    return sum;
}

fn solve2(buffers: [3][256]u8, nbuffers: [3][16]?Number) !usize {
    var sum: usize = 0;
    for (buffers[1], 0..) |char, i| if (char == '*') {
        var k: u8 = 0;
        var power: usize = 1;
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

    var sum1: usize = 0;
    var sum2: usize = 0;
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
