from collections import defaultdict

with open('regexp.txt', 'r', encoding='utf-8') as f:
    regexp = f.read().strip()


# <x<e>f>abc(x|<l|m>)

# <a>b(<x|c>|d)f
# abc<x|e>(b|d)a<x|(b|d)>a
# <x|<b|d>>m<a>(b|d)
# <<a>x<b>>d(b|k)x
# a<x|k>(n|d)ef<a<l>c>
# a<x<e>b>def(l|m)


print('Исходное регулярное выражение:')
print(regexp)

new_regexp = '$' + '$'.join(regexp) + '$'

print('\nРегулярное выражение с вставленными $:')
print(new_regexp)

positions = []
dollar_counter = 0

for i, char in enumerate(new_regexp):
    if char == '$':
        dollar_counter += 1
        if i == 0:
            symbol_before = None  
        else:
            symbol_before = new_regexp[i - 1]

        if i + 1 < len(new_regexp):
            symbol_after = new_regexp[i + 1]
        else:
            symbol_after = None

        positions.append({
            'dollar_number': dollar_counter,
            'symbol_before': symbol_before,
            'symbol_after': symbol_after,
            'index': None,
            'is_term_start': False,
            'is_term_end': False,
        })

opening_brackets = {'(': ')', '<': '>'}
closing_brackets = {')': '(', '>': '<'}

for i, pos in enumerate(positions):
    symbol_before = pos['symbol_before']

    if symbol_before is not None and symbol_before.isalpha():
        pos['is_term_end'] = True

    if i + 1 < len(positions):
        next_symbol_before = positions[i + 1]['symbol_before']
        if next_symbol_before is not None and next_symbol_before.isalpha():
            pos['is_term_start'] = True

index_counter = 0

for idx, pos in enumerate(positions):
    if idx == 0:
        pos['index'] = index_counter
        index_counter += 1
    else:
        symbol_before = pos['symbol_before']
        if symbol_before is not None and symbol_before.isalpha():
            pos['index'] = index_counter
            index_counter += 1

def apply_initial_index_rule(positions):
    stack = []
    for i, pos in enumerate(positions):
        symbol_before = pos['symbol_before']

        if symbol_before in opening_brackets:
            closing_bracket = opening_brackets[symbol_before]
            parent_index = positions[i - 1]['index'] if i > 0 else None

            stack.append({'closing_bracket': closing_bracket, 'parent_index': parent_index})

        elif symbol_before in closing_brackets:
            if stack and stack[-1]['closing_bracket'] == symbol_before:
                stack.pop()
            else:
                print(f"Несоответствующая закрывающая скобка {symbol_before} на позиции {i}")

        if (pos['is_term_start'] or pos['symbol_after'] in ('<', '(')) and pos['index'] is None and pos['symbol_before'] != '>':
            if stack and stack[-1]['parent_index'] is not None:
                pos['index'] = stack[-1]['parent_index']

apply_initial_index_rule(positions)

for i, pos in enumerate(positions):
    symbol_before = pos['symbol_before']

    if symbol_before in closing_brackets:
        opening_bracket = closing_brackets[symbol_before]

        nesting_level = 1
        end_indices = []
        j = i - 1

        while j >= 0:
            current_symbol = positions[j]['symbol_before']

            if current_symbol == symbol_before:
                nesting_level += 1
            elif current_symbol == opening_bracket:
                nesting_level -= 1
                if nesting_level == 0:
                    if opening_bracket == '<' and positions[j - 1]['index'] is not None:
                        end_indices.append(positions[j - 1]['index'])
                    break
            else:
                if positions[j]['is_term_end'] and positions[j]['index'] is not None:
                    end_indices.append(positions[j]['index'])
            j -= 1

        if end_indices:
            end_indices = list(set(end_indices))
            if pos['index'] is not None and not isinstance(pos['index'], list):
                pos['index'] = [pos['index']]
            if isinstance(pos['index'], list):
                pos['index'].extend(end_indices)
                pos['index'] = list(set(pos['index']))
            else:
                pos['index'] = end_indices

apply_initial_index_rule(positions)

def apply_third_rule(positions):
    i = 0
    while i < len(positions):
        pos = positions[i]
        symbol_before = pos['symbol_before']

        if symbol_before == '<':
            stack = [i]
            j = i + 1
            nested_term_start_positions = {len(stack): []}

            if pos['is_term_start'] and not pos['is_term_end']:
                nested_term_start_positions[len(stack)].append(i)

            while j < len(positions):
                current_symbol = positions[j]['symbol_before']

                if current_symbol == '<':
                    stack.append(j)
                    nested_term_start_positions[len(stack)] = []
                elif current_symbol == '>':
                    last_opening = stack.pop()
                    index_after_closing = positions[j]['index']

                    for idx in nested_term_start_positions[len(stack) + 1]:
                        positions[idx]['index'] = index_after_closing

                    del nested_term_start_positions[len(stack) + 1]

                    if not stack:
                        break
                if positions[j]['is_term_start'] and not positions[j]['is_term_end'] and stack and positions[j]['symbol_before'] != '>':
                    nested_term_start_positions[len(stack)].append(j)
                j += 1

            if stack:
                print(f"Несоответствующая открывающая скобка '<' на позиции {i}")
                i += 1
                continue

            i = j + 1
        else:
            i += 1

apply_third_rule(positions)

print('\nСписок мест ($) после применения третьего правила для итерационных скобок:')
for pos in positions:
    start_end = ''
    if pos['is_term_start']:
        start_end += 'начало терма; '
    if pos['is_term_end']:
        start_end += 'конец терма; '
    index_value = pos['index']
    if isinstance(index_value, list):
        index_value = ', '.join(map(str, index_value))
    print(
        f"Место {pos['dollar_number']}: символ перед ним - {pos['symbol_before']}, {start_end}индекс - {index_value}")


def build_transition_table_step_by_step(positions):
    transition_table = defaultdict(lambda: defaultdict(set))
    processed_indices = set()
    queue = [0]

    while queue:
        current_idx = queue.pop(0)
        processed_indices.add(current_idx)

        for pos in positions:
            if pos['is_term_start'] and pos['index'] is not None:
                if isinstance(pos['index'], list) and current_idx in pos['index'] or pos['index'] == current_idx:
                    symbol = pos['symbol_after']

                    to_indices = []
                    found_current_symbol = False

                    for search_pos in positions:
                        if found_current_symbol:
                            if search_pos['symbol_before'] == symbol:
                                if search_pos['index'] is not None:
                                    if isinstance(search_pos['index'], list):
                                        to_indices.extend(search_pos['index'])
                                    else:
                                        to_indices.append(search_pos['index'])
                                break
                        if search_pos == pos:
                            found_current_symbol = True

                    for to_index in to_indices:
                        transition_table[symbol][current_idx].add(to_index)
                        if to_index not in processed_indices and to_index not in queue:
                            queue.append(to_index)

    return transition_table

def print_transition_table(transition_table):
    all_indices = set()
    for symbol in transition_table:
        for from_idx in transition_table[symbol]:
            all_indices.add(from_idx)
            all_indices.update(transition_table[symbol][from_idx])
    sorted_indices = sorted(all_indices)

    header = ['x/Q'] + [str(idx) for idx in sorted_indices]
    print('\nТаблица переходов:')
    print('\t'.join(header))

    symbols = sorted(transition_table.keys())

    for symbol in symbols:
        row = [symbol]
        for idx in sorted_indices:
            if idx in transition_table[symbol]:
                to_indices = sorted(transition_table[symbol][idx])
                row.append(','.join(map(str, to_indices)))
            else:
                row.append('')
        print('\t'.join(row))

transition_table_step = build_transition_table_step_by_step(positions)
print_transition_table(transition_table_step)
