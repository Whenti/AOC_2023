const std = @import("std");
const split = std.mem.split;
const parse = std.fmt.parseUnsigned;

const Color = enum(u2) {
    red = 0,
    green = 1,
    blue = 2,
};
const LIMIT = [_]u32{ 12, 13, 14 };

fn solve(line: []const u8) ![2]u32 {
    var max = [_]u32{ 0, 0, 0 };
    var it = split(u8, line, ": ");
    const n = try parse(u8, it.next().?[5..], 10);
    var setIt = split(u8, it.next().?, "; ");
    while (setIt.next()) |setDesc| {
        var colorIt = split(u8, setDesc, ", ");
        while (colorIt.next()) |colorDesc| {
            var numberIt = split(u8, colorDesc, " ");
            const number = try parse(u8, numberIt.next().?, 10);
            const color = std.meta.stringToEnum(Color, numberIt.next().?).?;
            const idx = @intFromEnum(color);
            max[idx] = @max(max[idx], number);
        }
    }
    const ans2 = max[0] * max[1] * max[2];
    for (max, LIMIT) |m, l| if (m > l) return [_]u32{0, ans2};
    return [_]u32{n, ans2};
}

pub fn main() !void {
    const stdin = std.io.getStdIn().reader();
    var buffer: [256]u8 = undefined;

    var sum1: u32 = 0;
    var sum2: u32 = 0;
    while (try stdin.readUntilDelimiterOrEof(&buffer, '\n')) |line| {
        var ans = try solve(line);
        sum1 += ans[0];
        sum2 += ans[1];
    }
    std.debug.print("part 1: {}\n", .{sum1});
    std.debug.print("part 2: {}\n", .{sum2});
}
