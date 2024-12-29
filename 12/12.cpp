#include "../lib.hpp"

enum op_t {
    op_cpy,
    op_inc,
    op_dec,
    op_jnz
};

unordered_map<string, op_t> op_name = {
    { "cpy", op_cpy },
    { "inc", op_inc },
    { "dec", op_dec },
    { "jnz", op_jnz }
};

static int32_t reg[4] = { 0, 0, 1, 0 };
static int32_t reg_jmp;

struct val_t {
    union {
        int32_t *reg;
        int32_t im;
    };
    bool is_im;
};

struct cmd_t {
    op_t op;
    int32_t *reg;
    val_t v;
};

unordered_map<op_t, function<void(cmd_t)>> ops = {
    { op_cpy, [](cmd_t c) { (*c.reg) = c.v.is_im ? c.v.im : *c.v.reg; } },
    { op_inc, [](cmd_t c) { (*c.reg)++; } },
    { op_dec, [](cmd_t c) { (*c.reg)--; } },
    { op_jnz, [](cmd_t c) { if (*c.reg) reg_jmp = c.v.im; } }
};

int main() {
    const regex linerex2("(.*) (.*) (.*)");
    const regex linerex1("(.*) (.*)");
    vector<cmd_t> program;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        cmd_t cmd;
        smatch linematch;
        if (regex_match(s, linematch, linerex2) && linematch.size() == 4) {
            cmd.op = op_name[linematch[1].str()];
            string v1 = linematch[2].str(), v2 = linematch[3].str();
            if (cmd.op == op_jnz) {
                cmd.reg = &(reg[v1[0] - 'a']);
                cmd.v.im = stoi(v2);
            }
            else {
                if (isdigit(v1[0]) || v1[0] == '-') {
                    cmd.v.im = stoi(v1);
                    cmd.v.is_im = true;
                }
                else {
                    cmd.v.reg = &(reg[v1[0] - 'a']);
                    cmd.v.is_im = false;
                }
                cmd.reg = &(reg[v2[0] - 'a']);
            }
        }
        else if (regex_match(s, linematch, linerex1) && linematch.size() == 3) {
            cmd.op = op_name[linematch[1].str()];
            cmd.reg = &(reg[linematch[2].str()[0] - 'a']);
        }
        program.push_back(cmd);
    }

    int32_t ptr = 0;
    while (ptr < program.size()) {
        reg_jmp = 1;
        cmd_t &cmd = program[ptr];
        ops[cmd.op](cmd);
        ptr += reg_jmp;
    }

    cout << reg[0] << endl;

    return 0;
}

