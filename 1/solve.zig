const std = @import("std");

const NUMS = [_][]const u8{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

fn solve(line: []const u8, second: bool) !u8 {
    var first: ?u8 = null;
    var last: ?u8 = null;
    for (line, 0..) |c, i| {
        var digit: ?u8 = null;
        if (c >= '0' and c <= '9') {
            digit = c - '0';
        } else if (second) {
            for (NUMS, 0..) |num, d| {
                if (std.mem.startsWith(u8, line[i..], num)) {
                    digit = @intCast(d);
                }
            }
        }

        if (digit != null){
            if (first == null) {
                first = digit;
            }
            last = digit;
        }
    }
    return 10 * (first orelse return 0) + last.?;
}

pub fn main() !void {
    const stdin = std.io.getStdIn().reader();
    var buffer: [128]u8 = undefined;

    var sum1: u32 = 0;
    var sum2: u32 = 0;
    while (try stdin.readUntilDelimiterOrEof(&buffer, '\n')) |line| {
        sum1 += try solve(line, false);
        sum2 += try solve(line, true);
    }
    std.debug.print("part 1: {}\n", .{sum1});
    std.debug.print("part 2: {}\n", .{sum2});
}
